#ifndef VOTING_H
#define VOTING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Candidate structure — I might revisit the field sizes later
(50 chars for a name always feels arbitrary, but anyway…)
*/
typedef struct {
int id;
char name[50]; // Maybe make this dynamic at some point?
char party[30]; // Same thought here
int votes; // starting at 0 obviously
} Candidate;

/*
Voter info — kept pretty barebones.
Note: I think 1 = voted, 0 = didn’t vote,
but I should double-check when wiring the menu logic.
*/
typedef struct {
int id;
char name[50];
int voted;
} Voter;

/*
I know globals aren’t ideal, but
for this tiny project they make life easier.
Might refactor to a context struct someday.
*/
#define MAX_CANDIDATES 100
#define MAX_VOTERS 100

// using plain arrays for now; I'll switch to malloc/realloc later IF needed
Candidate candidates[MAX_CANDIDATES];
int num_candidates = 0;

Voter voters[MAX_VOTERS];
int num_voters = 0;

// Function prototypes — order is a bit random, but whatever for now
int add_candidate(char *cName, char *partyName); // maybe validate lengths?
int add_voter(char *vName);
int cast_vote(int voter_id, int cand_id); // TODO: maybe return different codes for errors
void display_results(); // prints summary — pretty straightforward

// Saving/loading the list — I keep forgetting the filename conventions
void save_data(const char *fpath);
void load_data(const char *fpath);

// Very simple text menu loop (not making it fancy for now)
void menu();

/* Small helper — I wrote this because scanf burns me every time.
Might add error messages if input is weird. */
int read_int();

#endif
