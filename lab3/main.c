#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "merkle_tree.h"

#define MAX_LINE_LEN 256
#define TARGET_NAME "\"Iacobesc Ionut\""

static void strip_newline(char *str) {
    size_t len = strlen(str);
    while (len > 0 && (str[len - 1] == '\n')) {
        str[--len] = '\0';
    }
}

int main(int argc, char *argv[]) {
    const char *filename = "students_2026.txt";

    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open file '%s'\n", filename);
        return EXIT_FAILURE;
    }

    MerkleTree *tree = create_merkle_tree();
    char line[MAX_LINE_LEN];

    printf("Reading lines from '%s'...\n", filename);
    while (fgets(line, sizeof(line), file)) {
        strip_newline(line);
        if (strlen(line) > 0) {
            add_element(tree, line);
        }
    }
    fclose(file);

    // Retrieve the master Root Hash
    const unsigned char *root_hash = get_root_hash(tree);

    if (!root_hash) {
        printf("File is empty or contains no valid lines.\n");
        free_merkle_tree(tree);
        return EXIT_SUCCESS;
    }

    printf("Successfully built Merkle Tree.\n");

    // Generate Merkle Proof for the target string
    printf("\nGenerating proof for target: \"%s\"...\n", TARGET_NAME);
    MerkleProof *proof = generate_proof(tree, TARGET_NAME);

    if (!proof) {
        printf("Result: Target \"%s\" was NOT found in the tree.\n", TARGET_NAME);
    } else {
		int cnt = get_proof_count(proof);
        printf("Proof generated (%d steps required).\n", cnt);
		for(int i = 0 ; i < cnt; i++) printf("%s,\n", hash_to_string(get_proof_sibling(proof,i)));

        bool is_valid = verify_proof(root_hash, TARGET_NAME, proof);

        if (is_valid) {
            printf("Verification SUCCESSFUL: \"%s\" exists in the Merkle Tree!\n", TARGET_NAME);
        } else {
            printf("Verification FAILED: The proof is invalid.\n");
        }
        free_merkle_proof(proof);


    }

    free_merkle_tree(tree);
    return EXIT_SUCCESS;
}