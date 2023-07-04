#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int MAX = 9;
string winner[MAX]; // Max number of candidates
int candidate_count; // Number of candidates
int voter_count;
int n = 1;
int temp;

typedef struct // Candidates have name and vote count
{
    string name;
    int votes;
}
candidate;

candidate candidates[MAX]; // Array of candidates

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n"); //check for invalid usage
        return 1;
    }
    candidate_count = argc - 1; // Populate array of candidates
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++) // Loop over all voters
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    voter_count = get_int("Number of voters: ");
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }
    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        temp = candidates[i - 1].votes;
        if (candidates[i].votes > temp)
        {
            winner[0] = candidates[i].name;
            n = 1;
        }
        else if (candidates[i].votes < temp)
        {
            n = 1;
        }
        else
        {
            for (int j = 0; j <= i; j++)
            {
                n++;
                winner[j] = candidates[j].name;
            }
        }
    }
    for (int i = 0; i <= n; i++)
    {
        if (winner[i] != NULL)
        {
            printf("%s\n", winner[i]);

        }
    }
}
