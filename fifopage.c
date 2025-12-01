#include <stdio.h>

void fifo(int pages[], int n, int frame_count) {
    int frame[50];
    int front = 0, page_faults = 0, page_hits = 0;

    for (int i = 0; i < frame_count; i++)
        frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < frame_count; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                page_hits++;
                break;
            }
        }

        if (!found) {
            frame[front] = pages[i];
            front = (front + 1) % frame_count;
            page_faults++;
        }
    }

    printf("\nFIFO Algorithm:\n");
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

    fifo(pages, n, frame_count);

    return 0;
}
