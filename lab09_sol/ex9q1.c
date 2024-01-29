#include <stdio.h>
#include <string.h>

#define MAX_WORDS 20
#define MAX_LINES 100
#define MAX_WORD_LENGTH 10

int min(int a, int b, int c) {
    if (a < b && a < c) return a;
    if (b < c) return b;
    return c;
}

int levenshteinDistance(char *word1, char *word2) {
    int len1 = strlen(word1);
    int len2 = strlen(word2);

    int dp[len1 + 1][len2 + 1];

    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else {
                dp[i][j] = min(
                    dp[i - 1][j] + 1,
                    dp[i][j - 1] + 1,
                    dp[i - 1][j - 1] + (word1[i - 1] == word2[j - 1] ? 0 : 1)
                );
            }
        }
    }

    return dp[len1][len2];
}

void correctSentence(char *sentence, char words[MAX_WORDS][MAX_WORD_LENGTH], int numWords) {
    char *token = strtok(sentence, " \n");
    while (token != NULL) {
        int minDistance = levenshteinDistance(token, words[0]);
        char correctWord[MAX_WORD_LENGTH];
        strcpy(correctWord, words[0]);

        for (int i = 1; i < numWords; i++) {
            int distance = levenshteinDistance(token, words[i]);
            if (distance < minDistance) {
                minDistance = distance;
                strcpy(correctWord, words[i]);
            }
        }

        printf("%s", correctWord);
        token = strtok(NULL, " \n");

        if (token != NULL) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    int numWords, numLines;
    scanf("%d %d", &numWords, &numLines);

    char words[MAX_WORDS][MAX_WORD_LENGTH];
    for (int i = 0; i < numWords; i++) {
        scanf("%s", words[i]);
    }

    char line[MAX_LINES * (MAX_WORDS * MAX_WORD_LENGTH + 1)];
    fgets(line, sizeof(line), stdin);

    for (int i = 0; i < numLines; i++) {
        fgets(line, sizeof(line), stdin);
        correctSentence(line, words, numWords);
    }

    return 0;
}
