#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAX 100
typedef struct 
{
    int id;
    char title[50];
    char category[30];
    int freq;
} Book;
Book library[MAX];
int n = 0;
// Save library to file
void saveLibrary() 
{
    FILE *fp = fopen("library.txt", "w");
    if (!fp) return;
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d,%s,%s,%d\n", library[i].id, library[i].title, library[i].category, library[i].freq);
    }
    fclose(fp);
}
// Load library from file
void loadLibrary() 
{
    FILE *fp = fopen("library.txt", "r");
    if (!fp) return;
    while (fscanf(fp, "%d,%49[^,],%29[^,],%d\n", &library[n].id, library[n].title, library[n].category, &library[n].freq) == 4) {
        n++;
    }
    fclose(fp);
}
// Add book
void addBook() 
{
    if (n >= MAX) 
    {
        printf("Library is full!\n");
        return;
    }
    printf("Enter Book ID: ");
    scanf("%d", &library[n].id);
    printf("Enter Book Title: ");
    getchar();
    fgets(library[n].title, sizeof(library[n].title), stdin);
    library[n].title[strcspn(library[n].title, "\n")] = '\0';
    printf("Enter Category: ");
    fgets(library[n].category, sizeof(library[n].category), stdin);
    library[n].category[strcspn(library[n].category, "\n")] = '\0';
    printf("Enter Access Frequency: ");
    scanf("%d", &library[n].freq);
    n++;
    saveLibrary();
    printf("Book added successfully!\n");
}
// Display all books
void displayBooks() 
{
    if (n == 0) 
    {
        printf("No books in library.\n");
        return;
    }
    int maxTitle = 5, maxCategory = 8;
    for (int i = 0; i < n; i++) 
    {
        int lenTitle = strlen(library[i].title);
        int lenCat = strlen(library[i].category);
        if (lenTitle > maxTitle) maxTitle = lenTitle;
        if (lenCat > maxCategory) maxCategory = lenCat;
    }
    printf("%-5s %-*s %-*s %-10s\n", "ID", maxTitle, "Title", maxCategory, "Category", "Frequency");
    for (int i = 0; i < 5 + maxTitle + maxCategory + 10 + 3; i++) printf("-");
    printf("\n");
    for (int i = 0; i < n; i++) 
    {
        printf("%-5d %-*s %-*s %-10d\n",
               library[i].id,
               maxTitle, library[i].title,
               maxCategory, library[i].category,
               library[i].freq);
    }
}
// Greedy sort by frequency (descending)
void greedyArrange() 
{
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = i + 1; j < n; j++) 
        {
            if (library[i].freq < library[j].freq) 
            {
                Book temp = library[i];
                library[i] = library[j];
                library[j] = temp;
            }
        }
    }
    saveLibrary();
    printf("Books arranged greedily by frequency.\n");
}
// Helper: sum of frequencies
int sum(int freq[], int i, int j) 
{
    int s = 0;
    for (int k = i; k <= j; k++) s += freq[k];
    return s;
}
// DP: Optimal BST cost and root table
int optimalBST(int freq[], int n, int root[MAX][MAX]) 
{
    int cost[MAX][MAX];
    for (int i = 0; i < n; i++) 
    {
        cost[i][i] = freq[i];
        root[i][i] = i;
    }
    for (int L = 2; L <= n; L++) 
    {
        for (int i = 0; i <= n - L; i++) 
        {
            int j = i + L - 1;
            cost[i][j] = INT_MAX;
            for (int r = i; r <= j; r++) 
            {
                int c = ((r > i) ? cost[i][r - 1] : 0) +
                        ((r < j) ? cost[r + 1][j] : 0) +
                        sum(freq, i, j);
                if (c < cost[i][j]) 
                {
                    cost[i][j] = c;
                    root[i][j] = r;
                }
            }
        }
    }
    return cost[0][n - 1];
}
// Recursive function to get in-order sequence from optimal BST
void inorderArrange(Book temp[], int root[MAX][MAX], int freqIdx[], int i, int j, int *idx) 
{
    if (i > j) return;
    int r = root[i][j];
    inorderArrange(temp, root, freqIdx, i, r - 1, idx);
    temp[*idx] = library[freqIdx[r]]; // place the book in new order
    (*idx)++;
    inorderArrange(temp, root, freqIdx, r + 1, j, idx);
}
// Sort library by frequency ascending before DP
void sortByFreqAscending() 
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++) 
        {
            if (library[i].freq > library[j].freq) 
            {
                Book temp = library[i];
                library[i] = library[j];
                library[j] = temp;
            }
        }
    }
}
// DP Optimal arrangement
void dpArrange() 
{
    if (n == 0) 
    {
        printf("No books available.\n");
        return;
    }
    // Sort ascending before DP
    sortByFreqAscending();
    int freq[MAX], freqIdx[MAX];
    for (int i = 0; i < n; i++) 
    {
        freq[i] = library[i].freq;
        freqIdx[i] = i;
    }
    int root[MAX][MAX];
    int cost = optimalBST(freq, n, root);
    Book temp[MAX];
    int idx = 0;
    inorderArrange(temp, root, freqIdx, 0, n - 1, &idx);
    // Copy back to library[]
    for (int i = 0; i < n; i++) library[i] = temp[i];
    saveLibrary();
    printf("Books arranged optimally using DP. Optimal Search Cost = %d\n", cost);
}
// Search for a book by ID
void searchBook() 
{
    int id;
    printf("Enter Book ID to search: ");
    scanf("%d", &id);
    for (int i = 0; i < n; i++) 
    {
        if (library[i].id == id) 
        {
            printf("Book Found: %s (%s), Frequency: %d\n", library[i].title, library[i].category, library[i].freq);
            return;
        }
    }
    printf("Book not found.\n");
}
// Borrow/return book
void borrowBook() 
{
    int id;
    printf("Enter Book ID to borrow/return: ");
    scanf("%d", &id);
    for (int i = 0; i < n; i++) 
    {
        if (library[i].id == id) 
        {
            library[i].freq++;
            printf("Book borrowed: %s. Frequency updated to %d\n", library[i].title, library[i].freq);
            saveLibrary();
            return;
        }
    }
    printf("Book not found.\n");
}
// Show statistics
void showStats() 
{
    if (n == 0) 
    {
        printf("No books available.\n");
        return;
    }
    int maxF = library[0].freq, minF = library[0].freq;
    int maxIdx = 0, minIdx = 0, sumF = 0;
    for (int i = 0; i < n; i++) 
    {
        if (library[i].freq > maxF) { maxF = library[i].freq; maxIdx = i; }
        if (library[i].freq < minF) { minF = library[i].freq; minIdx = i; }
        sumF += library[i].freq;
    }
    printf("Most accessed: %s (%d times)\n", library[maxIdx].title, maxF);
    printf("Least accessed: %s (%d times)\n", library[minIdx].title, minF);
    printf("Average frequency: %.2f\n", (float)sumF / n);
}
// Main menu
int main() 
{
    int choice;
    loadLibrary();
    while (1) {
        printf("\n===== Optimal Library Book Arrangement System =====\n");
        printf("1. Add Book\n2. Display Books\n3. Greedy Arrangement\n4. Optimal Arrangement (DP)\n");
        printf("5. Search Book\n6. Borrow/Return Book\n7. Show Statistics\n8. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: greedyArrange(); break;
            case 4: dpArrange(); break;
            case 5: searchBook(); break;
            case 6: borrowBook(); break;
            case 7: showStats(); break;
            case 8: saveLibrary(); exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}