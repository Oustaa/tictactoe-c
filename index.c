#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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

void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

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

int main_menu()
{
    int answer;

    printf("Welcome to tic tac toe:\n");

    do
    {
        printf("1 > To play against friend\n");
        printf("2 > To play against computer\n");
        printf("3 > To quit the game\n");
        printf("Enter your choise here: ");

        scanf("%d", &answer);

    } while (answer != 1 && answer != 2 && answer != 3);

    return answer;
}

void get_player_name(char **player_name)
{
    char local_player_name[255];

    printf("Enter player name: ");
    fgets(local_player_name, 255, stdin);

    size_t len = strlen(local_player_name);
    if (len > 0 && local_player_name[len - 1] == '\n')
    {
        local_player_name[len - 1] = '\0';
    }

    if (strlen(local_player_name) != 0)
    {
        *player_name = local_player_name;
    }

    clear_input_buffer();
}

int in_game_menu()
{
    int answer;

    printf("\nChoose an option:\n");

    do
    {
        printf("1 > Continue playing\n");
        printf("2 > Back to the menu\n");
        printf("Enter your choise here: ");

        scanf("%d", &answer);

    } while (answer != 1 && answer != 2);

    return answer;
}

void game(char *player_one_name, char *player_two_name)
{
    bool game_over = false;
    char played_spots[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    Player players[2] = {{"Player one", 0, {}, 0}, {"Player two", 0, {}, 0}};
    Player *players_ptr[] = {&players[0], &players[1]};
    int current_player_index = 0;
    int play_count = 0;
    int ties = 0;

    if (strlen(player_one_name) != 0)
    {
        players[0].name = player_one_name;
    }

    if (strlen(player_two_name) != 0)
    {
        players[1].name = player_two_name;
    }

    while (true)
    {
        if (game_over)
        {
            if (in_game_menu() == 2)
            {
                break;
            }
            else
            {
                printf("Game must countunu and resetevery thing");
            }
        }
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
                    players[current_player_index].score++;
                    game_over = true;
                }
            }
            current_player_index = current_player_index == 0 ? 1 : 0;
            if (play_count == 9)
            {
                printf("It's a tie!\n");
                ties++;
                game_over = true;
            }
        }
        printf("Score: %s - %d, %s - %d, Ties - %d\n", players[0].name, players[0].score, players[1].name, players[1].score, ties);
    }
}

int main()
{
    char *player_one_name, *player_two_name;
    int answer = main_menu();

    while (true)
    {
        if (answer == 1)
        {
            get_player_name(&player_one_name);
            get_player_name(&player_two_name);

            printf("################################");
            printf("player one name is %s\n", player_one_name);
            printf("player two name is %s\n", player_two_name);
            printf("################################");

            game(player_one_name, player_two_name);
        }
        else if (answer == 2)
        {
            printf("Playing with computer is not implemented yet\n");
        }
        else if (answer == 3)
        {
            break;
        }
    }
    return 0;
}
