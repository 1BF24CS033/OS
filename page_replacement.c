#include <stdio.h>
#include <limits.h>

void fifo(int pages[], int n, int num_frames) {
    int frames[num_frames];
    for (int i = 0; i < num_frames; i++) frames[i] = -1;
    int page_faults = 0, next = 0;

    printf("\nFIFO:\n");
    for (int i = 0; i < n; i++) {
        int page = pages[i], found = 0;
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) { found = 1; break; }
        }
        if (!found) {
            page_faults++;
            frames[next] = page;
            next = (next + 1) % num_frames;
        }
        printf("Page %d: ", page);
        for (int j = 0; j < num_frames; j++) printf("%d ", frames[j]);
        printf("\n");
    }
    printf("Total Page Faults (FIFO): %d\n", page_faults);
}

void lru(int pages[], int n, int num_frames) {
    int frames[num_frames], last_used[num_frames];
    for (int i = 0; i < num_frames; i++) { frames[i] = -1; last_used[i] = -1; }
    int page_faults = 0;

    printf("\nLRU Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int page = pages[i], found = 0;
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) { found = 1; last_used[j] = i; break; }
        }
        if (!found) {
            page_faults++;
            int placed = 0;
            for (int j = 0; j < num_frames; j++) {
                if (frames[j] == -1) { frames[j] = page; last_used[j] = i; placed = 1; break; }
            }
            if (!placed) {
                int lru_index = 0;
                for (int j = 1; j < num_frames; j++) {
                    if (last_used[j] < last_used[lru_index]) lru_index = j;
                }
                frames[lru_index] = page;
                last_used[lru_index] = i;
            }
        }
        printf("Page %d: ", page);
        for (int j = 0; j < num_frames; j++) printf("%d ", frames[j]);
        printf("\n");
    }
    printf("Total Page Faults (LRU): %d\n", page_faults);
}

void optimal(int pages[], int n, int num_frames) {
    int frames[num_frames];
    for (int i = 0; i < num_frames; i++) frames[i] = -1;
    int page_faults = 0;

    printf("\nOptimal Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int page = pages[i], found = 0;
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) { found = 1; break; }
        }
        if (!found) {
            page_faults++;
            int placed = 0;
            for (int j = 0; j < num_frames; j++) {
                if (frames[j] == -1) { frames[j] = page; placed = 1; break; }
            }
            if (!placed) {
                int farthest = -1, replace_index = -1;
                for (int j = 0; j < num_frames; j++) {
                    int next_use = INT_MAX;
                    for (int k = i + 1; k < n; k++) {
                        if (pages[k] == frames[j]) { next_use = k; break; }
                    }
                    if (next_use > farthest) {
                        farthest = next_use;
                        replace_index = j;
                    }
                }
                frames[replace_index] = page;
            }
        }
        printf("Page %d: ", page);
        for (int j = 0; j < num_frames; j++) printf("%d ", frames[j]);
        printf("\n");
    }
    printf("Total Page Faults (Optimal): %d\n", page_faults);
}

int main() {
    int num_frames, n;

    printf("Enter number of frames: ");
    scanf("%d", &num_frames);

    printf("Enter length of reference string: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the reference string (space-separated): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    fifo(pages, n, num_frames);
    optimal(pages, n, num_frames);
    lru(pages, n, num_frames);

    return 0;
}
