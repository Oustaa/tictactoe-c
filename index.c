#include <stdio.h>
#include <stdbool.h>

#define WINNING_SCHEMAS                                                                          \
    {                                                                                            \
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 4, 7}, {2, 5, 8}, {3, 6, 9}, {1, 5, 9}, { 7, 5, 3 } \
    }

typedef struct
{
    char *name;
    int score;
    char played_spots[6];
    int played_count;
} Player;

void draw_map(char played_spots[9])
{
    printf("-------------\n");
    for (int i = 0; i < 9; i++)
    {
        printf("| %c ", played_spots[i]);
        if ((i + 1) % 3 == 0)
        {
            printf("|\n-------------\n");
        }
    }
}

bool check_player_win(Player *player)
{
    char winning_schemas[][3] = WINNING_SCHEMAS;
    int num_schemas = sizeof(winning_schemas) / sizeof(winning_schemas[0]);

    for (int i = 0; i < num_schemas; i++)
    {
        int match_count = 0;

        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < player->played_count; k++)
            {
                // printf("player spot %d, tested spot %c\n", player->played_spots[k], winning_schemas[i][j]);
                if ((int)player->played_spots[k] == winning_schemas[i][j])
                {
                    match_count++;
                    break;
                }
            }
        }

        if (match_count == 3)
        {
            return true;
        }

        match_count = 0;
    }

    return false;
}

void play(Player *players[], int current_player_index, char played_spots[])
{
    int chosen_spot;
    Player *player = players[current_player_index];
    char mark = current_player_index == 0 ? 'X' : 'O';
    int tries = 0;

    do
    {
        if (tries == 1)
        {
            printf("Invalid spot! Please choose again.\n");
        }
        else
        {
            tries = 1;
        }
        printf("Player %s (%c), choose a spot (1-9): ", player->name, mark);
        scanf("%d", &chosen_spot);
    } while (chosen_spot < 1 || chosen_spot > 9 || played_spots[chosen_spot - 1] == 'X' || played_spots[chosen_spot - 1] == 'O');

    played_spots[chosen_spot - 1] = mark;

    player->played_spots[player->played_count] = chosen_spot;
    player->played_count += 1;

    draw_map(played_spots);
}

int main()
{
    bool game_over = false;
    char played_spots[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    Player players[2] = {{"Oussama", 0, {}, 0}, {"Kaoutar", 0, {}, 0}};
    Player *players_ptr[] = {&players[0], &players[1]};
    int current_player_index = 0;
    int play_count = 0;

    draw_map(played_spots);

    while (!game_over)
    {
        play(players_ptr, current_player_index, played_spots);
        play_count++;
        if (play_count >= 4)
        {
            bool is_player_win = check_player_win(&players[current_player_index]);
            if (is_player_win == true)
            {
                printf("%s wins!\n", players[current_player_index].name);
                game_over = true;
            }
        }
        current_player_index = current_player_index == 0 ? 1 : 0;
    }

    return 0;
}
