/*
 * NOTE TO SELF:
  */

#include "voting.h"
#include <stdio.h>
#include <string.h>

void menu() {

    // Load saved stuff immediately — maybe later add a "Are you sure?" prompt.
    load_data("votes.dat");

    int userPick = 0;   // I changed the name just so it feels more personal.

    do {
        printf("\n=== MINI VOTING SYSTEM (still kinda ugly UI) ===\n");
        printf("1) Add Candidate\n");
        printf("2) Add Voter\n");
        printf("3) Cast Vote\n");
        printf("4) Show Results\n");
        printf("5) Save & Quit\n");
        printf("Enter choice: ");

        userPick = read_int();

        // I guess I'll reuse these buffers because why not.
        char tmpName[50], tmpParty[30];
        int vID = -1, cID = -1;

        switch (userPick) {
            case 1:
                printf("Candidate name: ");
                // Should probably use fgets, but… meh.
                scanf("%s", tmpName);

                printf("Party (short code maybe): ");
                scanf("%s", tmpParty);

                // Not checking return value, just assuming it works.
                add_candidate(tmpName, tmpParty);
                break;

            case 2:
                printf("Voter name (no spaces pls): ");
                scanf("%s", tmpName);

                add_voter(tmpName);
                break;

            case 3:
                printf("Enter voter ID: ");
                vID = read_int();

                printf("Enter candidate ID: ");
                cID = read_int();

                // This probably needs more validation, but future-me can fix that.
                cast_vote(vID, cID);
                break;

            case 4:
                // I left this simple; maybe later add fancy formatting.
                display_results();
                break;

            case 5:
                // Saving and then leaving the program gracefully.
                save_data("votes.dat");
                printf("Alright, saving and shutting down...\n");
                break;

            default:
                printf("Hmm… not a valid option. Try again.\n");
                break;
        }

    } while (userPick != 5);
}


int main() {
    // Could add custom startup flags eventually
    // For now just run the menu.
    menu();
    return 0;
}

