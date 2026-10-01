#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LINE 500
#define MAX_FILENAME 100

const char *keywords[] = {
    "password",
    "passwd",
    "pwd",
    "secret",
    "api_key",
    "apikey",
    "client_secret",
    "auth_token",
    "token",
    "bearer",
    "private_key",
    "begin rsa private key",
    "begin openssh private key",
    "ssh-rsa",

    /* AWS */
    "akia",
    "asia",
    "aws_secret_access_key",

    /* GitHub */
    "ghp_",
    "gho_",
    "ghu_",
    "ghs_",
    "ghr_",
    "github_pat_",

    /* Google */
    "aiza",
    "gocspx-",
    "ya29.",

    /* Slack */
    "xoxb-",
    "xoxp-",
    "xoxa-",
    "xoxr-",
    "xapp-",

    /* Stripe */
    "sk_live_",
    "sk_test_",
    "rk_live_",
    "rk_test_",

    /* Other common servies */
    "sg.",
    "sk-ant-",
    "sk-proj-",
    "shpat_",
    "shpss_",
    "dop_v1_",
    "lin_api_",
    "npm_",
    "pypi-",
    "eyj"
};
const int NUM_KEYWORDS = sizeof(keywords) / sizeof(keywords[0]);

void to_lowercase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

int main() {
    char filename[MAX_FILENAME];
    char line[MAX_LINE];
    char lower_line[MAX_LINE];
    int line_num = 0;
    int secrets_found = 0;

    printf("=== Simple Api and Password Detector ===\n");
    printf("Enter the file name to scan: ");
    scanf("%99s", filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file '%s'\n", filename);
        return 1;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        line_num++;

        strncpy(lower_line, line, sizeof(lower_line) - 1);
        lower_line[sizeof(lower_line) - 1] = '\0';
        to_lowercase(lower_line);

        if (strstr(lower_line, "secretscan-ignore") != NULL) {
            continue;
        }

        for (int i = 0; i < NUM_KEYWORDS; i++) {
            if (strstr(lower_line, keywords[i]) != NULL) {
                printf("[ALERT] Line %d: possible secret found (matched \"%s\")\n",
                       line_num, keywords[i]);
                secrets_found++;
            }
        }
    }

    fclose(file);

    printf("\n");
    printf("Scanned %d line(s).\n", line_num);

    if (secrets_found > 0) {
        printf("RESULT: %d possible secret(s) found. Commit should be BLOCKED.\n",
               secrets_found);
        return 1;
    } else {
        printf("RESULT: No secrets found. Commit passed.\n");
        return 0;
    }
}
