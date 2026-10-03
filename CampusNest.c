#include <stdio.h>
#include <string.h>

/* CONSTANTS */
#define MAX_STUDENTS   100
#define MAX_ROOMS      100
#define MAX_FEES       100
#define MAX_VISITORS   100
#define MAX_REQUESTS   100

#define NAME_LEN       40
#define STATUS_LEN     20
#define ISSUE_LEN      80
#define TIME_LEN       12
#define GENDER_LEN     8
#define CONTACT_LEN    16
#define EMAIL_LEN      40
#define DATE_LEN       12

/* STRUCTURE 1 — Student  (Member 1) */
typedef struct {
    int  id;
    char name[NAME_LEN];
    int  age;
    char gender[GENDER_LEN];
    char contact[CONTACT_LEN];
    char email[EMAIL_LEN];
    int  roomNo;
    char enrollDate[DATE_LEN];
} Student;

/* STRUCTURE 2 — Room  (Member 2) */
typedef struct {
    int  roomNo;
    int  capacity;
    int  occupied;
    char type[NAME_LEN];      /* Single / Double / Triple */
    char status[STATUS_LEN];  /* Available / Full / Maintenance */
    float pricePerMonth;
} Room;

/* STRUCTURE 3 — Fee  (Member 3) */
typedef struct {
    int   feeId;
    int   studentId;
    float amount;
    char  month[DATE_LEN];
    char  status[STATUS_LEN]; /* Paid / Unpaid / Partial */
    char  payDate[DATE_LEN];
} Fee;

/* STRUCTURE 4 — Visitor  (Member 4) */
typedef struct {
    int  visitorId;
    char visitorName[NAME_LEN];
    int  studentId;
    char relation[NAME_LEN];
    char checkIn[TIME_LEN];
    char checkOut[TIME_LEN];
    char visitDate[DATE_LEN];
} Visitor;

/* STRUCTURE 5 — MaintenanceRequest  (Member 5) */
typedef struct {
    int  reqId;
    int  roomNo;
    char issue[ISSUE_LEN];
    char priority[STATUS_LEN]; /* Low / Medium / High */
    char status[STATUS_LEN];   /* Pending / In-Progress / Resolved */
    char reportDate[DATE_LEN];
} MaintenanceRequest;

/* GLOBAL ARRAYS OF STRUCTURES */
Student   students[MAX_STUDENTS];
Room      rooms[MAX_ROOMS];
Fee       fees[MAX_FEES];
Visitor   visitors[MAX_VISITORS];
MaintenanceRequest requests[MAX_REQUESTS];

int studentCount = 0;
int roomCount    = 0;
int feeCount     = 0;
int visitorCount = 0;
int requestCount = 0;

/* UTILITY FUNCTIONS */

/* Strip trailing \r and \n (handles CRLF files) */
static void strip_crlf(char *s)
{
    size_t len = strlen(s);
    while (len > 0 && (s[len-1] == '\r' || s[len-1] == '\n'))
        s[--len] = '\0';
}

/* Drain stdin buffer */
static void clear_buffer(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

/* Read integer with validation */
static int read_int(const char *prompt, int *out)
{
    printf("%s", prompt);
    if (scanf("%d", out) != 1) {
        clear_buffer();
        printf("  [!] Invalid input. Please enter a number.\n");
        return 0;
    }
    clear_buffer();
    return 1;
}

/* Read float with validation */
static int read_float(const char *prompt, float *out)
{
    printf("%s", prompt);
    if (scanf("%f", out) != 1) {
        clear_buffer();
        printf("  [!] Invalid input. Please enter a number.\n");
        return 0;
    }
    clear_buffer();
    return 1;
}

/* Read a line (allows spaces), strip CRLF */
static void read_line(const char *prompt, char *buf, int len)
{
    printf("%s", prompt);
    if (fgets(buf, len, stdin))
        strip_crlf(buf);
    else
        buf[0] = '\0';
}

/* Convert string to uppercase for case-insensitive compare */
static char to_upper_char(char c)
{
    if (c >= 'a' && c <= 'z') return (char)(c - 32);
    return c;
}

static void str_upper(char *dest, const char *src, int len)
{
    int i;
    for (i = 0; i < len - 1 && src[i]; i++)
        dest[i] = to_upper_char(src[i]);
    dest[i] = '\0';
}

/* Check if string contains only digits */
static int is_numeric(const char *s)
{
    if (!s || !*s) return 0;
    while (*s) {
        if (*s < '0' || *s > '9') return 0;
        s++;
    }
    return 1;
}

/* Zero out a block of memory (replaces memset — no stdlib needed) */
static void zero_mem(void *ptr, int size)
{
    char *p = (char *)ptr;
    int i;
    for (i = 0; i < size; i++)
        p[i] = 0;
}

/* Print a divider line */
static void divider(void)
{
    printf("  %-50s\n", "--------------------------------------------------");
}

/* MEMBER 1 — STUDENT MANAGEMENT*/

/* M1-F1: Check if student ID already exists */
static int student_id_exists(int id)
{
    int i;
    for (i = 0; i < studentCount; i++)
        if (students[i].id == id) return 1;
    return 0;
}

/* M1-F2: Add a new student with full validation */
static void student_add(void)
{
    if (studentCount >= MAX_STUDENTS) {
        printf("  [!] Student list is full.\n");
        return;
    }

    Student s;
    zero_mem(&s, sizeof(s));

    if (!read_int("  Student ID    : ", &s.id)) return;
    if (student_id_exists(s.id)) {
        printf("  [!] Student ID %d already exists.\n", s.id);
        return;
    }
    if (s.id <= 0) {
        printf("  [!] ID must be a positive number.\n");
        return;
    }

    read_line("  Full Name      : ", s.name, NAME_LEN);
    if (strlen(s.name) == 0) { printf("  [!] Name cannot be empty.\n"); return; }

    if (!read_int("  Age           : ", &s.age)) return;
    if (s.age < 16 || s.age > 60) {
        printf("  [!] Age must be between 16 and 60.\n");
        return;
    }

    read_line("  Gender (M/F)   : ", s.gender, GENDER_LEN);
    read_line("  Contact No     : ", s.contact, CONTACT_LEN);

    if (!is_numeric(s.contact)) {
        printf("  [!] Contact number must contain digits only.\n");
        return;
    }

    read_line("  Email          : ", s.email, EMAIL_LEN);
    if (!read_int("  Room Number    : ", &s.roomNo)) return;
    read_line("  Enroll Date    : ", s.enrollDate, DATE_LEN);

    students[studentCount++] = s;
    printf("  [+] Student '%s' added successfully.\n", s.name);
}

/* M1-F3: Display all students in a formatted table */
static void student_view_all(void)
{
    if (studentCount == 0) {
        printf("  No student records found.\n");
        return;
    }
    printf("\n  %-6s %-22s %-4s %-6s %-14s %-6s\n",
           "ID", "Name", "Age", "Gender", "Contact", "Room");
    divider();
    int i;
    for (i = 0; i < studentCount; i++) {
        Student *s = &students[i];
        printf("  %-6d %-22s %-4d %-6s %-14s %-6d\n",
               s->id, s->name, s->age, s->gender, s->contact, s->roomNo);
    }
    divider();
    printf("  Total students: %d\n", studentCount);
}

/* M1-F4: Search student by ID or name (pointer demo) */
static void student_search(void)
{
    int choice;
    printf("  Search by: 1) ID   2) Name\n");
    if (!read_int("  Choice: ", &choice)) return;

    int i, found = 0;

    if (choice == 1) {
        int id;
        if (!read_int("  Enter ID: ", &id)) return;
        for (i = 0; i < studentCount; i++) {
            Student *p = &students[i];   /* pointer to struct */
            if (p->id == id) {
                printf("\n  ID      : %d\n", p->id);
                printf("  Name    : %s\n", p->name);
                printf("  Age     : %d\n", p->age);
                printf("  Gender  : %s\n", p->gender);
                printf("  Contact : %s\n", p->contact);
                printf("  Email   : %s\n", p->email);
                printf("  Room    : %d\n", p->roomNo);
                printf("  Enrolled: %s\n", p->enrollDate);
                found = 1;
                break;
            }
        }
    } else if (choice == 2) {
        char query[NAME_LEN], nameUp[NAME_LEN], sUp[NAME_LEN];
        read_line("  Enter Name: ", query, NAME_LEN);
        str_upper(nameUp, query, NAME_LEN);
        printf("\n  %-6s %-22s %-4s %-6s\n", "ID", "Name", "Age", "Room");
        divider();
        for (i = 0; i < studentCount; i++) {
            str_upper(sUp, students[i].name, NAME_LEN);
            if (strstr(sUp, nameUp)) {
                printf("  %-6d %-22s %-4d %-6d\n",
                       students[i].id, students[i].name,
                       students[i].age, students[i].roomNo);
                found = 1;
            }
        }
    } else {
        printf("  [!] Invalid option.\n");
        return;
    }

    if (!found) printf("  No matching student found.\n");
}

/* M1-F5: Sort students by ID (bubble sort on array of structs) */
static void student_sort_by_id(void)
{
    int i, j;
    Student temp;
    for (i = 0; i < studentCount - 1; i++) {
        for (j = 0; j < studentCount - 1 - i; j++) {
            if (students[j].id > students[j+1].id) {
                temp = students[j];
                students[j] = students[j+1];
                students[j+1] = temp;
            }
        }
    }
    printf("  [+] Students sorted by ID.\n");
    student_view_all();
}

/* M1-F6: Update student room assignment */
static void student_update_room(void)
{
    int id, newRoom, i;
    if (!read_int("  Student ID    : ", &id)) return;
    if (!read_int("  New Room No   : ", &newRoom)) return;

    for (i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            students[i].roomNo = newRoom;
            printf("  [+] Room updated for student '%s'.\n", students[i].name);
            return;
        }
    }
    printf("  Student ID %d not found.\n", id);
}

/* M1-F7: Delete student by ID */
static void student_delete(void)
{
    int id, i, found = 0;
    if (!read_int("  Enter Student ID to delete: ", &id)) return;

    for (i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            found = 1;
            /* Shift array left */
            int j;
            for (j = i; j < studentCount - 1; j++)
                students[j] = students[j+1];
            studentCount--;
            printf("  [+] Student deleted.\n");
            break;
        }
    }
    if (!found) printf("  Student ID %d not found.\n", id);
}

/* MEMBER 2 — ROOM MANAGEMENT */

/* M2-F1: Check if room number exists */
static int room_exists(int roomNo)
{
    int i;
    for (i = 0; i < roomCount; i++)
        if (rooms[i].roomNo == roomNo) return 1;
    return 0;
}

/* M2-F2: Add a new room */
static void room_add(void)
{
    if (roomCount >= MAX_ROOMS) {
        printf("  [!] Room list is full.\n");
        return;
    }

    Room r;
    zero_mem(&r, sizeof(r));

    if (!read_int("  Room Number   : ", &r.roomNo)) return;
    if (room_exists(r.roomNo)) {
        printf("  [!] Room %d already exists.\n", r.roomNo);
        return;
    }

    read_line("  Type (Single/Double/Triple): ", r.type, NAME_LEN);
    if (!read_int("  Capacity      : ", &r.capacity)) return;
    if (r.capacity < 1 || r.capacity > 10) {
        printf("  [!] Capacity must be between 1 and 10.\n");
        return;
    }
    if (!read_float("  Price/Month   : ", &r.pricePerMonth)) return;
    if (r.pricePerMonth <= 0) {
        printf("  [!] Price must be positive.\n");
        return;
    }

    r.occupied = 0;
    strncpy(r.status, "Available", STATUS_LEN - 1);

    rooms[roomCount++] = r;
    printf("  [+] Room %d added.\n", r.roomNo);
}

/* M2-F3: View all rooms in formatted table */
static void room_view_all(void)
{
    if (roomCount == 0) {
        printf("  No room records found.\n");
        return;
    }
    printf("\n  %-6s %-10s %-10s %-10s %-12s %-14s\n",
           "Room", "Type", "Capacity", "Occupied", "Status", "Price/Month");
    divider();
    int i;
    for (i = 0; i < roomCount; i++) {
        Room *r = &rooms[i];
        printf("  %-6d %-10s %-10d %-10d %-12s %-14.2f\n",
               r->roomNo, r->type, r->capacity, r->occupied,
               r->status, r->pricePerMonth);
    }
    divider();
    printf("  Total rooms: %d\n", roomCount);
}

/* M2-F4: Search room by number */
static void room_search(void)
{
    int roomNo, i;
    if (!read_int("  Enter Room Number: ", &roomNo)) return;

    for (i = 0; i < roomCount; i++) {
        Room *r = &rooms[i];
        if (r->roomNo == roomNo) {
            printf("\n  Room No    : %d\n", r->roomNo);
            printf("  Type       : %s\n", r->type);
            printf("  Capacity   : %d\n", r->capacity);
            printf("  Occupied   : %d\n", r->occupied);
            printf("  Status     : %s\n", r->status);
            printf("  Price/Month: %.2f\n", r->pricePerMonth);
            return;
        }
    }
    printf("  Room %d not found.\n", roomNo);
}

/* M2-F5: Update room status */
static void room_update_status(void)
{
    int roomNo, i;
    if (!read_int("  Room Number: ", &roomNo)) return;

    for (i = 0; i < roomCount; i++) {
        if (rooms[i].roomNo == roomNo) {
            read_line("  New Status (Available/Full/Maintenance): ",
                      rooms[i].status, STATUS_LEN);
            printf("  [+] Room %d status updated to '%s'.\n",
                   roomNo, rooms[i].status);
            return;
        }
    }
    printf("  Room %d not found.\n", roomNo);
}

/* M2-F6: Show only available rooms */
static void room_view_available(void)
{
    int i, count = 0;
    printf("\n  --- Available Rooms ---\n");
    printf("  %-6s %-10s %-10s %-14s\n", "Room", "Type", "Capacity", "Price/Month");
    divider();
    for (i = 0; i < roomCount; i++) {
        char up[STATUS_LEN];
        str_upper(up, rooms[i].status, STATUS_LEN);
        if (strstr(up, "AVAILABLE")) {
            printf("  %-6d %-10s %-10d %-14.2f\n",
                   rooms[i].roomNo, rooms[i].type,
                   rooms[i].capacity, rooms[i].pricePerMonth);
            count++;
        }
    }
    if (count == 0) printf("  No available rooms.\n");
}

/* M2-F7: Sort rooms by room number */
static void room_sort(void)
{
    int i, j;
    Room temp;
    for (i = 0; i < roomCount - 1; i++) {
        for (j = 0; j < roomCount - 1 - i; j++) {
            if (rooms[j].roomNo > rooms[j+1].roomNo) {
                temp = rooms[j];
                rooms[j] = rooms[j+1];
                rooms[j+1] = temp;
            }
        }
    }
    printf("  [+] Rooms sorted by room number.\n");
    room_view_all();
}

/* M2-F8: Delete a room */
static void room_delete(void)
{
    int roomNo, i, found = 0;
    if (!read_int("  Room Number to delete: ", &roomNo)) return;

    for (i = 0; i < roomCount; i++) {
        if (rooms[i].roomNo == roomNo) {
            found = 1;
            int j;
            for (j = i; j < roomCount - 1; j++)
                rooms[j] = rooms[j+1];
            roomCount--;
            printf("  [+] Room %d deleted.\n", roomNo);
            break;
        }
    }
    if (!found) printf("  Room %d not found.\n", roomNo);
}

/* MEMBER 3 — FEE MANAGEMENT */

/* M3-F1: Generate next fee ID */
static int next_fee_id(void)
{
    int max = 1000, i;
    for (i = 0; i < feeCount; i++)
        if (fees[i].feeId >= max) max = fees[i].feeId + 1;
    return max;
}

/* M3-F2: Add a fee record */
static void fee_add(void)
{
    if (feeCount >= MAX_FEES) {
        printf("  [!] Fee list is full.\n");
        return;
    }

    Fee f;
    zero_mem(&f, sizeof(f));

    f.feeId = next_fee_id();
    if (!read_int("  Student ID    : ", &f.studentId)) return;

    if (!student_id_exists(f.studentId)) {
        printf("  [!] Student ID %d does not exist.\n", f.studentId);
        return;
    }

    if (!read_float("  Amount (LKR)  : ", &f.amount)) return;
    if (f.amount <= 0) {
        printf("  [!] Amount must be positive.\n");
        return;
    }

    read_line("  Month (e.g. Jan-2025): ", f.month, DATE_LEN);
    read_line("  Status (Paid/Unpaid/Partial): ", f.status, STATUS_LEN);
    read_line("  Payment Date   : ", f.payDate, DATE_LEN);

    fees[feeCount++] = f;
    printf("  [+] Fee record added. Fee ID: %d\n", f.feeId);
}

/* M3-F3: View all fee records */
static void fee_view_all(void)
{
    if (feeCount == 0) {
        printf("  No fee records found.\n");
        return;
    }
    printf("\n  %-6s %-10s %-12s %-12s %-10s %-12s\n",
           "FeeID", "StudID", "Amount(LKR)", "Month", "Status", "Pay Date");
    divider();
    int i;
    for (i = 0; i < feeCount; i++) {
        Fee *f = &fees[i];
        printf("  %-6d %-10d %-12.2f %-12s %-10s %-12s\n",
               f->feeId, f->studentId, f->amount,
               f->month, f->status, f->payDate);
    }
    divider();
}

/* M3-F4: Search fee records by student ID */
static void fee_search_by_student(void)
{
    int sid, i, found = 0;
    if (!read_int("  Enter Student ID: ", &sid)) return;

    printf("\n  %-6s %-12s %-12s %-10s %-12s\n",
           "FeeID", "Amount(LKR)", "Month", "Status", "Pay Date");
    divider();

    for (i = 0; i < feeCount; i++) {
        if (fees[i].studentId == sid) {
            Fee *f = &fees[i];
            printf("  %-6d %-12.2f %-12s %-10s %-12s\n",
                   f->feeId, f->amount, f->month, f->status, f->payDate);
            found = 1;
        }
    }
    if (!found) printf("  No fee records for student ID %d.\n", sid);
}

/* M3-F5: Calculate total collected fees (passing array to function) */
static float fee_total_collected(Fee *arr, int count)
{
    float total = 0;
    int i;
    for (i = 0; i < count; i++) {
        char up[STATUS_LEN];
        str_upper(up, arr[i].status, STATUS_LEN);
        if (strcmp(up, "PAID") == 0)
            total += arr[i].amount;
    }
    return total;
}

static void fee_summary(void)
{
    float collected = fee_total_collected(fees, feeCount);
    float total     = 0;
    int   unpaid    = 0, i;

    for (i = 0; i < feeCount; i++) {
        total += fees[i].amount;
        char up[STATUS_LEN];
        str_upper(up, fees[i].status, STATUS_LEN);
        if (strcmp(up, "UNPAID") == 0) unpaid++;
    }

    printf("\n  --- Fee Summary ---\n");
    printf("  Total records     : %d\n", feeCount);
    printf("  Total billed      : LKR %.2f\n", total);
    printf("  Total collected   : LKR %.2f\n", collected);
    printf("  Outstanding       : LKR %.2f\n", total - collected);
    printf("  Unpaid records    : %d\n", unpaid);
}

/* M3-F6: Update fee status */
static void fee_update_status(void)
{
    int feeId, i;
    if (!read_int("  Enter Fee ID: ", &feeId)) return;

    for (i = 0; i < feeCount; i++) {
        if (fees[i].feeId == feeId) {
            read_line("  New Status (Paid/Unpaid/Partial): ",
                      fees[i].status, STATUS_LEN);
            read_line("  Payment Date: ", fees[i].payDate, DATE_LEN);
            printf("  [+] Fee ID %d status updated.\n", feeId);
            return;
        }
    }
    printf("  Fee ID %d not found.\n", feeId);
}

/* M3-F7: Sort fees by amount descending */
static void fee_sort_by_amount(void)
{
    int i, j;
    Fee temp;
    for (i = 0; i < feeCount - 1; i++) {
        for (j = 0; j < feeCount - 1 - i; j++) {
            if (fees[j].amount < fees[j+1].amount) {
                temp = fees[j];
                fees[j] = fees[j+1];
                fees[j+1] = temp;
            }
        }
    }
    printf("  [+] Fees sorted by amount (highest first).\n");
    fee_view_all();
}

/* MEMBER 4 — VISITOR MANAGEMENT */

/* M4-F1: Generate next visitor ID */
static int next_visitor_id(void)
{
    int max = 2000, i;
    for (i = 0; i < visitorCount; i++)
        if (visitors[i].visitorId >= max) max = visitors[i].visitorId + 1;
    return max;
}

/* M4-F2: Log a new visitor */
static void visitor_add(void)
{
    if (visitorCount >= MAX_VISITORS) {
        printf("  [!] Visitor log is full.\n");
        return;
    }

    Visitor v;
    zero_mem(&v, sizeof(v));
    v.visitorId = next_visitor_id();

    read_line("  Visitor Name   : ", v.visitorName, NAME_LEN);
    if (strlen(v.visitorName) == 0) { printf("  [!] Name cannot be empty.\n"); return; }

    if (!read_int("  Student ID     : ", &v.studentId)) return;
    if (!student_id_exists(v.studentId)) {
        printf("  [!] Student ID %d does not exist.\n", v.studentId);
        return;
    }

    read_line("  Relation       : ", v.relation, NAME_LEN);
    read_line("  Visit Date     : ", v.visitDate, DATE_LEN);
    read_line("  Check-In Time  : ", v.checkIn, TIME_LEN);
    read_line("  Check-Out Time : ", v.checkOut, TIME_LEN);

    visitors[visitorCount++] = v;
    printf("  [+] Visitor logged. Visitor ID: %d\n", v.visitorId);
}

/* M4-F3: View all visitors */
static void visitor_view_all(void)
{
    if (visitorCount == 0) {
        printf("  No visitor records found.\n");
        return;
    }
    printf("\n  %-6s %-20s %-8s %-12s %-10s %-10s\n",
           "VID", "Visitor Name", "StudID", "Relation", "Check-In", "Check-Out");
    divider();
    int i;
    for (i = 0; i < visitorCount; i++) {
        Visitor *v = &visitors[i];
        printf("  %-6d %-20s %-8d %-12s %-10s %-10s\n",
               v->visitorId, v->visitorName, v->studentId,
               v->relation, v->checkIn, v->checkOut);
    }
    divider();
    printf("  Total visitors logged: %d\n", visitorCount);
}

/* M4-F4: Search visitors by student ID */
static void visitor_search_by_student(void)
{
    int sid, i, found = 0;
    if (!read_int("  Enter Student ID: ", &sid)) return;

    printf("\n  Visitors for Student ID %d:\n", sid);
    divider();
    for (i = 0; i < visitorCount; i++) {
        if (visitors[i].studentId == sid) {
            Visitor *v = &visitors[i];
            printf("  ID:%d | Name:%-20s | Date:%-12s | In:%-8s | Out:%-8s\n",
                   v->visitorId, v->visitorName, v->visitDate,
                   v->checkIn, v->checkOut);
            found = 1;
        }
    }
    if (!found) printf("  No visitors found for student %d.\n", sid);
}

/* M4-F5: Count visitors per student (passing array of struct to function) */
static int visitor_count_for_student(Visitor *arr, int count, int studentId)
{
    int i, n = 0;
    for (i = 0; i < count; i++)
        if (arr[i].studentId == studentId) n++;
    return n;
}

static void visitor_count_report(void)
{
    if (studentCount == 0) { printf("  No students registered.\n"); return; }
    printf("\n  --- Visitor Count Per Student ---\n");
    printf("  %-8s %-22s %-12s\n", "Stud ID", "Name", "Visitor Count");
    divider();
    int i;
    for (i = 0; i < studentCount; i++) {
        int cnt = visitor_count_for_student(visitors, visitorCount, students[i].id);
        printf("  %-8d %-22s %-12d\n", students[i].id, students[i].name, cnt);
    }
}

/* M4-F6: Sort visitors by date (string sort) */
static void visitor_sort_by_date(void)
{
    int i, j;
    Visitor temp;
    for (i = 0; i < visitorCount - 1; i++) {
        for (j = 0; j < visitorCount - 1 - i; j++) {
            if (strcmp(visitors[j].visitDate, visitors[j+1].visitDate) > 0) {
                temp = visitors[j];
                visitors[j] = visitors[j+1];
                visitors[j+1] = temp;
            }
        }
    }
    printf("  [+] Visitors sorted by date.\n");
    visitor_view_all();
}

/* M4-F7: Delete visitor record */
static void visitor_delete(void)
{
    int vid, i, found = 0;
    if (!read_int("  Visitor ID to delete: ", &vid)) return;

    for (i = 0; i < visitorCount; i++) {
        if (visitors[i].visitorId == vid) {
            found = 1;
            int j;
            for (j = i; j < visitorCount - 1; j++)
                visitors[j] = visitors[j+1];
            visitorCount--;
            printf("  [+] Visitor record deleted.\n");
            break;
        }
    }
    if (!found) printf("  Visitor ID %d not found.\n", vid);
}

/* MEMBER 5 — MAINTENANCE MANAGEMENT */

/* M5-F1: Generate next request ID */
static int next_req_id(void)
{
    int max = 3000, i;
    for (i = 0; i < requestCount; i++)
        if (requests[i].reqId >= max) max = requests[i].reqId + 1;
    return max;
}

/* M5-F2: Add a maintenance request */
static void request_add(void)
{
    if (requestCount >= MAX_REQUESTS) {
        printf("  [!] Request list is full.\n");
        return;
    }

    MaintenanceRequest r;
    zero_mem(&r, sizeof(r));
    r.reqId = next_req_id();

    if (!read_int("  Room Number   : ", &r.roomNo)) return;
    if (!room_exists(r.roomNo)) {
        printf("  [!] Room %d does not exist.\n", r.roomNo);
        return;
    }

    read_line("  Issue          : ", r.issue, ISSUE_LEN);
    if (strlen(r.issue) == 0) { printf("  [!] Issue cannot be empty.\n"); return; }

    read_line("  Priority (Low/Medium/High): ", r.priority, STATUS_LEN);
    read_line("  Report Date    : ", r.reportDate, DATE_LEN);
    strncpy(r.status, "Pending", STATUS_LEN - 1);

    requests[requestCount++] = r;
    printf("  [+] Request logged. Request ID: %d\n", r.reqId);
}

/* M5-F3: View all maintenance requests */
static void request_view_all(void)
{
    if (requestCount == 0) {
        printf("  No maintenance records found.\n");
        return;
    }
    printf("\n  %-6s %-6s %-30s %-8s %-14s %-12s\n",
           "ReqID", "Room", "Issue", "Priority", "Status", "Date");
    divider();
    int i;
    for (i = 0; i < requestCount; i++) {
        MaintenanceRequest *r = &requests[i];
        printf("  %-6d %-6d %-30s %-8s %-14s %-12s\n",
               r->reqId, r->roomNo, r->issue,
               r->priority, r->status, r->reportDate);
    }
    divider();
    printf("  Total requests: %d\n", requestCount);
}

/* M5-F4: Update request status */
static void request_update_status(void)
{
    int reqId, i;
    if (!read_int("  Request ID: ", &reqId)) return;

    for (i = 0; i < requestCount; i++) {
        if (requests[i].reqId == reqId) {
            read_line("  New Status (Pending/In-Progress/Resolved): ",
                      requests[i].status, STATUS_LEN);
            printf("  [+] Request %d status updated.\n", reqId);
            return;
        }
    }
    printf("  Request ID %d not found.\n", reqId);
}

/* M5-F5: Search requests by room number */
static void request_search_by_room(void)
{
    int roomNo, i, found = 0;
    if (!read_int("  Enter Room Number: ", &roomNo)) return;

    printf("\n  Requests for Room %d:\n", roomNo);
    divider();
    for (i = 0; i < requestCount; i++) {
        if (requests[i].roomNo == roomNo) {
            MaintenanceRequest *r = &requests[i];
            printf("  ID:%-6d | Issue:%-30s | Priority:%-8s | Status:%-14s\n",
                   r->reqId, r->issue, r->priority, r->status);
            found = 1;
        }
    }
    if (!found) printf("  No requests for Room %d.\n", roomNo);
}

/* M5-F6: Count pending requests (passing array of struct to function) */
static int count_pending(MaintenanceRequest *arr, int count)
{
    int i, n = 0;
    for (i = 0; i < count; i++) {
        char up[STATUS_LEN];
        str_upper(up, arr[i].status, STATUS_LEN);
        if (strcmp(up, "PENDING") == 0) n++;
    }
    return n;
}

static void request_summary(void)
{
    int pending  = count_pending(requests, requestCount);
    int resolved = 0, inprog = 0, i;
    for (i = 0; i < requestCount; i++) {
        char up[STATUS_LEN];
        str_upper(up, requests[i].status, STATUS_LEN);
        if (strcmp(up, "RESOLVED")    == 0) resolved++;
        if (strcmp(up, "IN-PROGRESS") == 0) inprog++;
    }
    printf("\n  --- Maintenance Summary ---\n");
    printf("  Total requests   : %d\n", requestCount);
    printf("  Pending          : %d\n", pending);
    printf("  In-Progress      : %d\n", inprog);
    printf("  Resolved         : %d\n", resolved);
}

/* Helper: sort rank for priority (High=0, Medium=1, Low=2) */
static int priority_rank(const char *p)
{
    char up[STATUS_LEN];
    str_upper(up, p, STATUS_LEN);
    if (strcmp(up, "HIGH")   == 0) return 0;
    if (strcmp(up, "MEDIUM") == 0) return 1;
    return 2;
}

/* M5-F7: Sort requests by priority (High first) */
static void request_sort_by_priority(void)
{
    int i, j;
    MaintenanceRequest temp;
    for (i = 0; i < requestCount - 1; i++) {
        for (j = 0; j < requestCount - 1 - i; j++) {
            if (priority_rank(requests[j].priority) >
                priority_rank(requests[j+1].priority)) {
                temp = requests[j];
                requests[j] = requests[j+1];
                requests[j+1] = temp;
            }
        }
    }
    printf("  [+] Requests sorted by priority (High first).\n");
    request_view_all();
}

/* M5-F8: Delete a maintenance request */
static void request_delete(void)
{
    int reqId, i, found = 0;
    if (!read_int("  Request ID to delete: ", &reqId)) return;

    for (i = 0; i < requestCount; i++) {
        if (requests[i].reqId == reqId) {
            found = 1;
            int j;
            for (j = i; j < requestCount - 1; j++)
                requests[j] = requests[j+1];
            requestCount--;
            printf("  [+] Request %d deleted.\n", reqId);
            break;
        }
    }
    if (!found) printf("  Request ID %d not found.\n", reqId);
}

/* MENUS */

static void student_menu(void)
{
    int c = -1;
    while (c != 0) {
        printf("\n  ===  MEMBER 1: STUDENT MANAGEMENT  ===\n");
        printf("  1) Add Student\n");
        printf("  2) View All Students\n");
        printf("  3) Search Student\n");
        printf("  4) Update Room Assignment\n");
        printf("  5) Delete Student\n");
        printf("  6) Sort by ID\n");
        printf("  0) Back to Main Menu\n");
        divider();
        if (!read_int("  Choice: ", &c)) continue;
        switch (c) {
            case 1: student_add();         break;
            case 2: student_view_all();    break;
            case 3: student_search();      break;
            case 4: student_update_room(); break;
            case 5: student_delete();      break;
            case 6: student_sort_by_id();  break;
            case 0: break;
            default: printf("  [!] Invalid choice.\n");
        }
    }
}

static void room_menu(void)
{
    int c = -1;
    while (c != 0) {
        printf("\n  ===  MEMBER 2: ROOM MANAGEMENT  ===\n");
        printf("  1) Add Room\n");
        printf("  2) View All Rooms\n");
        printf("  3) Search Room\n");
        printf("  4) Update Room Status\n");
        printf("  5) View Available Rooms\n");
        printf("  6) Sort Rooms\n");
        printf("  7) Delete Room\n");
        printf("  0) Back to Main Menu\n");
        divider();
        if (!read_int("  Choice: ", &c)) continue;
        switch (c) {
            case 1: room_add();            break;
            case 2: room_view_all();       break;
            case 3: room_search();         break;
            case 4: room_update_status();  break;
            case 5: room_view_available(); break;
            case 6: room_sort();           break;
            case 7: room_delete();         break;
            case 0: break;
            default: printf("  [!] Invalid choice.\n");
        }
    }
}

static void fee_menu(void)
{
    int c = -1;
    while (c != 0) {
        printf("\n  ===  MEMBER 3: FEE MANAGEMENT  ===\n");
        printf("  1) Add Fee Record\n");
        printf("  2) View All Fees\n");
        printf("  3) Search by Student ID\n");
        printf("  4) Update Fee Status\n");
        printf("  5) Fee Summary\n");
        printf("  6) Sort by Amount\n");
        printf("  0) Back to Main Menu\n");
        divider();
        if (!read_int("  Choice: ", &c)) continue;
        switch (c) {
            case 1: fee_add();                 break;
            case 2: fee_view_all();            break;
            case 3: fee_search_by_student();   break;
            case 4: fee_update_status();       break;
            case 5: fee_summary();             break;
            case 6: fee_sort_by_amount();      break;
            case 0: break;
            default: printf("  [!] Invalid choice.\n");
        }
    }
}

static void visitor_menu(void)
{
    int c = -1;
    while (c != 0) {
        printf("\n  ===  MEMBER 4: VISITOR MANAGEMENT  ===\n");
        printf("  1) Log Visitor\n");
        printf("  2) View All Visitors\n");
        printf("  3) Search by Student ID\n");
        printf("  4) Visitor Count Report\n");
        printf("  5) Sort by Date\n");
        printf("  6) Delete Visitor Record\n");
        printf("  0) Back to Main Menu\n");
        divider();
        if (!read_int("  Choice: ", &c)) continue;
        switch (c) {
            case 1: visitor_add();                 break;
            case 2: visitor_view_all();            break;
            case 3: visitor_search_by_student();   break;
            case 4: visitor_count_report();        break;
            case 5: visitor_sort_by_date();        break;
            case 6: visitor_delete();              break;
            case 0: break;
            default: printf("  [!] Invalid choice.\n");
        }
    }
}

static void maintenance_menu(void)
{
    int c = -1;
    while (c != 0) {
        printf("\n  ===  MEMBER 5: MAINTENANCE MANAGEMENT  ===\n");
        printf("  1) Add Request\n");
        printf("  2) View All Requests\n");
        printf("  3) Update Request Status\n");
        printf("  4) Search by Room\n");
        printf("  5) Maintenance Summary\n");
        printf("  6) Sort by Priority\n");
        printf("  7) Delete Request\n");
        printf("  0) Back to Main Menu\n");
        divider();
        if (!read_int("  Choice: ", &c)) continue;
        switch (c) {
            case 1: request_add();            break;
            case 2: request_view_all();       break;
            case 3: request_update_status();  break;
            case 4: request_search_by_room(); break;
            case 5: request_summary();        break;
            case 6: request_sort_by_priority();break;
            case 7: request_delete();         break;
            case 0: break;
            default: printf("  [!] Invalid choice.\n");
        }
    }
}

/* MAIN */
int main(void)
{
    int choice = -1;

    while (choice != 0) {
        printf("\n--- CAMPUSNEST: MAIN MENU ---\n");
        printf("  1) Student Management\n");
        printf("  2) Room Management   \n");
        printf("  3) Fee Management    \n");
        printf("  4) Visitor Management\n");
        printf("  5) Maintenance Mgmt  \n");
        printf("  0) Exit\n");
        divider();
        if (!read_int("  Choice: ", &choice)) continue;

        switch (choice) {
            case 1: student_menu();     break;
            case 2: room_menu();        break;
            case 3: fee_menu();         break;
            case 4: visitor_menu();     break;
            case 5: maintenance_menu(); break;
            case 0: break;
            default: printf("  [!] Invalid choice.\n");
        }
    }

    return 0;
}