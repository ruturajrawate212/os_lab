#include <stdio.h>

int find_lru(int time[], int frame_count) {
    int min = time[0], pos = 0;

    for (int i = 1; i < frame_count; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

void lru(int pages[], int n, int frame_count) {
    int frame[50], time[50];
    int counter = 0, page_faults = 0, page_hits = 0;

    for (int i = 0; i < frame_count; i++) {
        frame[i] = -1;
        time[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < frame_count; j++) {
            if (frame[j] == pages[i]) {
                counter++;
                time[j] = counter;
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
                pos = find_lru(time, frame_count);
            }

            frame[pos] = pages[i];
            counter++;
            time[pos] = counter;
            page_faults++;
        }
    }

    printf("\nLRU Algorithm:\n");
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

    lru(pages, n, frame_count);

    return 0;
}
