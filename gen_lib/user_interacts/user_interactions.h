#ifndef GREEKLATINGSQ_USER_INTERACTIONS_H
#define GREEKLATINGSQ_USER_INTERACTIONS_H

enum ExecutionLogMode_enum
{
    EXECUTION_LOG_MODE_NONE,
    EXECUTION_LOG_MODE_HEARTBEAT,
    EXECUTION_LOG_MODE_COUNTDOWN
};
typedef enum ExecutionLogMode_enum ExecutionLogMode;

ExecutionLogMode chooseLogMode(int argc, char * argv[]);
struct _IO_FILE;
typedef struct _IO_FILE FILE;
int getValue(FILE * input);

int scanfInt();
void printfInt(const int * val);

double scanfDouble();
void printfDouble(const double * val);


#endif //GREEKLATINGSQ_USER_INTERACTIONS_H
