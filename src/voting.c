/*
 * NOTE TO FUTURE ME:
 * I left comments mostly for myself. Some redundant stuff too.
 */

#include "voting.h"
#include <string.h>   // I always forget this one...
#include <stdio.h>    // ...and this too.

// Adding a new candidate — returns its "internal" slot index (not ID)
int add_candidate(char *cName, char *cParty) {   
    // Quick sanity check before we do anything dangerous
    if (num_candidates >= MAX_CANDIDATES) {
        printf("Err: Too many candidates already.\n");
        return -1;   
    }

    // I like doing a temp index just so I can read it easier later
    int slot = num_candidates;  
    candidates[slot].id = slot + 1;  // Still 1-based IDs… not sure why but I'm sticking to it.

    // Copying strings manually — should probably check lengths, but eh.
    strcpy(candidates[slot].name, cName);
    strcpy(candidates[slot].party, cParty);

    candidates[slot].votes = 0;

    // I keep forgetting that post-increment returns the old value, but I'm using it anyway.
    return num_candidates++;
}


// Add a new voter — returns index just like above
int add_voter(char *personName) {
    if (num_voters >= MAX_VOTERS) {
        printf("Err: No more room for voters.\n");
        return -1;
    }

    int vSlot = num_voters;
    voters[vSlot].id = vSlot + 1;
    strcpy(voters[vSlot].name, personName);

    // 0 means they haven't voted (I should use a bool someday)
    voters[vSlot].voted = 0;

    // Again with the post-increment. Might revisit later…
    return num_voters++;
}


// Cast a vote — returns 1 if successful, 0 if fail
int cast_vote(int voterID, int candID) {

    // Loop through voters; this could be faster with direct indexing,
    // but safety first (and also I forgot if IDs always match index)
    for (int ii = 0; ii < num_voters; ii++) {
        if (voters[ii].id == voterID) {

            if (voters[ii].voted) {
                printf("Hey, voter %d already voted.\n", voterID);
                return 0;
            }

            // Now hunt for the candidate
            for (int jj = 0; jj < num_candidates; jj++) {
                if (candidates[jj].id == candID) {
                    candidates[jj].votes++;
                    voters[ii].voted = 1;

                    printf("Vote recorded for candidate %d (finally!).\n", candID);
                    return 1;
                }
            }

            // If we got here, candidate was never found
            printf("Candidate ID %d doesn't seem right.\n", candID);
            return 0;
        }
    }

    // Voter ID was invalid
    printf("Could not find voter %d.\n", voterID);
    return 0;
}


// Shows all results and winner (if any)
void display_results() {

    printf("\n=== RESULTS (not very fancy but works) ===\n");

    int tally = 0;
    for (int x = 0; x < num_candidates; x++) {
        printf("Candidate %d: %s (%s) -> %d vote(s)\n",
            candidates[x].id,
            candidates[x].name,
            candidates[x].party,
            candidates[x].votes);

        tally += candidates[x].votes;
    }

    if (tally == 0) {
        printf("Nobody voted yet… awkward.\n");
        return;
    }

    // Just max votes… ties not handled but oh well
    int top = -1;
    char winnerBuf[64];  // I made this slightly bigger than needed.

    for (int x = 0; x < num_candidates; x++) {
        if (candidates[x].votes > top) {
            top = candidates[x].votes;
            strcpy(winnerBuf, candidates[x].name);
        }
    }

    printf("Winner: %s with %d vote(s)\n", winnerBuf, top);
    printf("=========================================\n");
}


// Save data — I kept the binary I/O but added tiny messages
void save_data(const char *fname) {

    FILE *fp = fopen(fname, "wb");
    if (!fp) {
        printf("Couldn't open %s to save. :(\n", fname);
        return;
    }

    // I know this is repetitive but it's clearer in my head this way
    fwrite(&num_candidates, sizeof(int), 1, fp);
    fwrite(candidates, sizeof(Candidate), num_candidates, fp);

    fwrite(&num_voters, sizeof(int), 1, fp);
    fwrite(voters, sizeof(Voter), num_voters, fp);

    fclose(fp);
    printf("Saved everything into %s.\n", fname);
}


// Load data — same idea as save
void load_data(const char *fname) {

    FILE *fp = fopen(fname, "rb");
    if (!fp) {
        printf("No saved data found for %s.\n", fname);
        return;
    }

    fread(&num_candidates, sizeof(int), 1, fp);
    fread(candidates, sizeof(Candidate), num_candidates, fp);

    fread(&num_voters, sizeof(int), 1, fp);
    fread(voters, sizeof(Voter), num_voters, fp);

    fclose(fp);
    printf("Loaded data from %s.\n", fname);
}


// Read an integer from user — minimal validation
int read_int() {
    int tempNum;

    // scanf returning non-1 means "oops"
    if (scanf("%d", &tempNum) != 1) {

        // Clear leftover characters — this loop feels clunky but works
        while (getchar() != '\n') {
            /* was thinking of printing each char for fun debugging */
        }

        printf("Hey, not a number! Try again.\n");
        return -1;
    }

    return tempNum;
}

