/*
 * Regular expression implementation.
 * Supports only ( | ) * + ?.  No escapes.
 * Compiles to NFA and then simulates NFA
 * using Thompson's algorithm.
 *
 * See also http://swtch.com/~rsc/regexp/ and
 * Thompson, Ken.  Regular Expression Search Algorithm,
 * Communications of the ACM 11(6) (June 1968), pp. 419-422.
 * 
 * Copyright (c) 2007 Russ Cox.
 * Can be distributed under the MIT license, see bottom of file.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Convert infix regexp re to postfix notationa. Insert . as explicit
   concatenation operator. */

char *re2post(char *re) {
  int nalt, natom;
  static char buf[8000];
  char *dst;
  struct {
    int nalt;
    int natom;
  } paren[100], *p;

  p = paren;
  dst = buf;
  nalt = 0;
  natom = 0;
  if (strlen(re) >= sizeof buf/2) {
    return NULL;
  }

  for (; *re; re++) {
    switch (*re) {
    case '(':
      if (natom > 1) {
        --natom;
        *dst++ = '.';
      }
      if (p >= paren+100) {
        return NULL;
      }
      p->nalt = nalt;
      p->natom = natom;
      p++;
      nalt = 0;
      natom = 0;
      break;
    case '|':
      if (natom == 0) {
        return NULL;
      }
      while (--natom > 0) {
        *dst++ = '.';
      }
      nalt++;
      break;
    case ')':
      if (p == paren) {
        return NULL;
      }
      if (natom == 0) {
        return NULL;
      }
      while (--natom > 0) {
        *dst++ = '.';
      }
      for (; nalt > 0; nalt--) {
        *dst++ = '|';
      }
      --p;
      nalt = p->nalt;
      natom = p->natom;
      natom++;
      break;
    case '*':
    case '+':
    case '?':
      if (natom == 0) {
        return NULL;
      }
      *dst++ = *re;
      break;
    default:
      if (natom > 1) {
        --natom;
        *dst++ = '.';
      }
      *dst++ = *re;
      natom++;
      break;
    }
  }
  if (p != paren) {
    return NULL;
  }
  while (--natom > 0) {
    *dst++ = '.';
  }
  for (; nalt > 0; nalt--) {
    *dst++ = '|';
  }
  *dst = 0;
  return buf;
}


/* State represents one of the following NFA fragments, depending on the value of c:
   c                |--> out
   O ---> out   O --|             Match
                    |--> out1
   c < 256      c == 256(Split)   c == 257

*/

enum {
      Split = 256,
      Match = 257
};

typedef struct State {
  int c;
  struct State *out;
  struct State *out1;
  int lastlist;
} State;

State matchstate = { Match };   /* matching state */

int nstate;
State* state(int c, State *out, State *out1) {
  State *s;
  nstate++;
  s = malloc(sizeof(State));
  s->c = c;
  s->out = out;
  s->out1 = out1;
  s->lastlist = 0;
  return s;
}

/* since the out pointers are always uninitialized, we use themselves to store
   Ptrlists */
typedef union Ptrlist {
  union Ptrlist *next;
  State *s;
} Ptrlist;

typedef struct Frag {
  State *start;
  Ptrlist *out;
} Frag;

Frag frag(State *start, Ptrlist *out) {
  Frag f = {start, out};
  return f;
}

/* Create singleton Ptrlist containing just outp */
Ptrlist *list1(State **outp) {
  Ptrlist *p;
  p = (Ptrlist *) outp;
  p->next = NULL;
  return p;
}

/* Join two lists and return the combination */
Ptrlist *append(Ptrlist *l1, Ptrlist *l2) {
  if (l1 != NULL) {
    Ptrlist *old1;
    old1 = l1;
    while (l1->next) {
      l1 = l1->next;
    }
    l1->next = l2;
    return old1;
  } else {
    return l2;
  }
}

/* Patch the list of states at out to point to start */
void patch(Ptrlist *l, State *s) {
  /* s is the starting state */
  Ptrlist *next;
  for (; l; l=next) {
    next = l->next;
    l->s = s;
  }
}

/* convert postfix regular expression to NFA, return start state */
State *post2nfa(char *postfix) {
  char *p;
  Frag stack[1000], *stackp, e1, e2, e;
  State *s;

#define push(s) *stackp++ = s
#define pop() *--stackp

  stackp = stack;
  for (p=postfix; *p; p++) {
    switch (*p) {
    case '.':
      e2 = pop();
      e1 = pop();
      patch(e1.out, e2.start);
      push(frag(e1.start, e2.out));
      break;
    case '|':
      e2 = pop();
      e1 = pop();
      s = state(Split, e1.start, e2.start);
      push(frag(s, append(e1.out, e2.out)));
      break;
    case '?':
      e = pop();
      s = state(Split, e.start, NULL);
      push(frag(s, append(e.out, list1(&s->out1))));
      break;
    case '*':
      e = pop();
      s = state(Split, e.start, NULL);
      patch(e.out, s);
      push(frag(s, list1(&s->out1)));
      break;
    case '+':
      e = pop();
      s = state(Split, e.start, NULL);
      patch(e.out, s);
      push(frag(e.start, list1(&s->out1)));
      break;
    default:
      s = state(*p, NULL, NULL);
      push(frag(s, list1(&s->out)));
      break;
    }
  }

  e = pop();
  if (stackp != stack) {
    return NULL;
  }
  patch(e.out, &matchstate);
  return e.start;

#undef pop
#undef push
}


typedef struct List {
  State **s;
  int n;
} List;

List l1, l2;
static int listid;

void addstate(List *l, State *s) {
  /* since we have state pointing to its start, we will have duplicate states.
     listid is used to detect if state s is already in the list */
  if (s == NULL || s->lastlist == listid) {
    return;
  }
  s->lastlist = listid;
  if (s->c == Split) {
    /* follow unlabeled arrows */
    addstate(l, s->out);
    addstate(l, s->out1);
  } else {
    l->s[l->n++] = s;
  }
}

List *startlist(State *start, List *l) {
  l->n = 0;
  listid++;
  addstate(l, start);
  return l;
}

/* Step the NFA from the states in clist past the character c, to create next
   NFA state set nlist. */
void step(List *clist, int c, List *nlist) {
  int i;
  State *s;

  listid++;
  /* every states in nlist are removed */
  nlist->n = 0;
  for (i=0; i<clist->n; i++) {
    s = clist->s[i];
    if (s->c == c) {
      /* s will never be a split state, so s->out1 is not needed */
      addstate(nlist, s->out);
    }
  }
}

int ismatch(List *l) {
  int i;
  for (i=0; i<l->n; i++) {
    /* if any states in the final list is accepted, then nfa reaches matchstate */
    if (l->s[i] == &matchstate) {
      return 1;
    }
  }
  return 0;
}

/* Run NFA to determine whether it matches s. */
int match(State *start, char *s) {
  int c;
  List *clist, *nlist, *t;

  clist = startlist(start, &l1);
  nlist = &l2;
  for (; *s; s++) {
    c = *s & 0xFF;
    step(clist, c, nlist);
    /* swap clist, nlist */
    t = clist;
    clist = nlist;
    nlist = t;
  }
  return ismatch(clist);
}


int main(int argc, char **argv) {
	int i;
	char *post;
	State *start;

	if(argc < 3){
		fprintf(stderr, "usage: nfa regexp string...\n");
		return 1;
	}

	post = re2post(argv[1]);
	if(post == NULL){
		fprintf(stderr, "bad regexp %s\n", argv[1]);
		return 1;
	} else {
    fprintf(stdout, "postfix: %s\n", post);
  }

	start = post2nfa(post);
	if(start == NULL){
		fprintf(stderr, "error in post2nfa %s\n", post);
		return 1;
	}

	l1.s = malloc(nstate*sizeof l1.s[0]);
	l2.s = malloc(nstate*sizeof l2.s[0]);
	for(i=2; i<argc; i++)
		if(match(start, argv[i]))
			printf("%s\n", argv[i]);
	return 0;
}


/*
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the
 * Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the
 * Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
 * KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS
 * OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
