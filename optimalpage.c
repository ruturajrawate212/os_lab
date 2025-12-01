#include <stdio.h>

int find_optimal(int pages[], int n, int frame[], int frame_count, int index) {
    int farthest = index, pos = -1;

    for (int i = 0; i < frame_count; i++) {
        int found = 0;
        for (int j = index; j < n; j++) {
            if (frame[i] == pages[j]) {
                found = 1;
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (!found)
            return i;
    }

    return (pos == -1) ? 0 : pos;
}

void optimal(int pages[], int n, int frame_count) {
    int frame[50];
    int page_faults = 0, page_hits = 0;

    for (int i = 0; i < frame_count; i++)
        frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < frame_count; j++) {
            if (frame[j] == pages[i]) {
                page_hits++;
                found = 1;
                break;
            }
        }

        if (!found) {
            int pos;
            if (frame[0] == -1 || frame[1] == -1 || frame[2] == -1) {
                for (int k = 0; k < frame_count; k++) {
                    if (frame[k] == -1) {
                        pos = k;
                        break;
                    }
                }
            } else {
                pos = find_optimal(pages, n, frame, frame_count, i + 1);
            }

            frame[pos] = pages[i];
            page_faults++;
        }
    }

    printf("\nOptimal Algorithm:\n");
    printf("Page Faults = %d\n", page_faults);
    printf("Page Hits   = %d\n", page_hits);
}

int main() {
    int n, frame_count;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter reference string: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &frame_count);

    optimal(pages, n, frame_count);

    return 0;
}
