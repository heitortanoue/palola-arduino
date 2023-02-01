#ifndef __TYPES_H__
#define __TYPES_H__

enum MachineStatus {
    MACHINE_STATUS_FREE,
    MACHINE_STATUS_BUSY,
};

enum MealStatus {
    MEAL_STATUS_PENDING,
    MEAL_STATUS_ACCEPTED,
    MEAL_STATUS_REJECTED,
    MEAL_STATUS_FULL,
    MEAL_STATUS_NO_MEALS,
};

typedef struct {
    const char* name;
    struct Date {
        int hours;
        int minutes;
    } date;
} MealGroup;

typedef struct {
    String id;
    MealStatus status;
    float foodQuantity;
} Meal;

#endif