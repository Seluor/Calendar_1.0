#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>

std::string weekdays[4] = {
  "1 day", "2 day", "3 day", "4 day"
};  //Если нужно добавить или убрать день недели, то тебе сюда

int daysInMonths[12] = {
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};

struct monthLine {
    std::string months;
    std::string weekLine;
    std::string days[10] = { "", "", "", "", "", "", "", "", "", "" };
    int amountOfWeeks = 0;
};

bool isLeapYear(int year) {
    if (year % 400 == 0) {
        return true;
    }
    if (year % 100 == 0) {
        return false;
    }
    if (year % 4 == 0) {
        return true;
    }
    return false;
}

int firstDayOfMonth(int year, int month) {
    int shifts[12] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
    int shift = shifts[month - 1];

    if (isLeapYear(year) and (month > 2)) {
        shift += 1;
    };

    year = (year - 1) % 400;
    int century = year / 100;
    int index = ((4 * century) + (year % 100)) % 28;

    int weekday = (index + (index / 4)) + shift;

    return (weekday % 4);
}

int main() {
    int year;
    std::cout << "Enter year: ";
    std::cin  >> year;

    monthLine blocks[6]; //Если нужно добавить или убрать месяц, то тебе сюда

    blocks[0].months += "1 month" + std::string(40, ' ') +
        "2 month";
    blocks[1].months += "3 month" + std::string(42, ' ') +
        "4 month";
    blocks[2].months += "5 month" + std::string(43, ' ') +
        "6 month";
    blocks[3].months += "7 month" + std::string(40, ' ') +
        "8 month";
    blocks[4].months += "9 month" + std::string(40, ' ') +
        "10 month";
    blocks[5].months += "11 month" + std::string(40, ' ') +
        "12 month";

    for (int blockIndex = 0; blockIndex < 6; ++blockIndex) {
        for (int weekColumns = 0; weekColumns < 2; ++weekColumns) {
            for (int weekdayIndex = 0; weekdayIndex < 4; ++weekdayIndex) {
                blocks[blockIndex].weekLine += weekdays[weekdayIndex] + std::string(3, ' ');
            }
            blocks[blockIndex].weekLine += std::string(5, ' ');
        }
    }

    int blockIndex = 0;
    int weekIndex;

    for (int monthIndex = 1; monthIndex < 13; ++monthIndex) {
        weekIndex = 0;

        int numberInWeek = 0;
        int spacesBeforeFirstDayMultiplier = firstDayOfMonth(year, monthIndex);
        while (spacesBeforeFirstDayMultiplier) {
            blocks[blockIndex].days[weekIndex] += std::string(6, ' ');
            --spacesBeforeFirstDayMultiplier;
            ++numberInWeek;
        }
        //расстояние между днями недели  
        blocks[blockIndex].days[weekIndex] += "  ";
        for (int dayIndex = 1; dayIndex < daysInMonths[monthIndex - 1] + 1; ++dayIndex) {
            if (dayIndex < 10) {
                blocks[blockIndex].days[weekIndex] += " " + std::to_string(dayIndex);
                blocks[blockIndex].days[weekIndex] += std::string(6, ' ');
            }
            else {
                blocks[blockIndex].days[weekIndex] += std::to_string(dayIndex);
                blocks[blockIndex].days[weekIndex] += std::string(6, ' ');
            }
            ++numberInWeek;

            if (numberInWeek == 4) {
                blocks[blockIndex].days[weekIndex] += std::string(5, ' ');
                numberInWeek = 0;
                ++weekIndex;
            }

            int spacesAfterLastDay;
            if (monthIndex == 2 && isLeapYear(year) && dayIndex == 28) {
                blocks[blockIndex].days[weekIndex] += std::to_string(dayIndex);
                spacesAfterLastDay = (4 - numberInWeek + 1) * 2;
                blocks[blockIndex].days[weekIndex] += std::string(spacesAfterLastDay, ' ');
            }
            else if (dayIndex + 1 > daysInMonths[monthIndex - 1]) {
                spacesAfterLastDay = (4 - numberInWeek) * 5;
                blocks[blockIndex].days[weekIndex] += std::string(spacesAfterLastDay, ' ');
            }
        }

        if (weekIndex > blocks[blockIndex].amountOfWeeks) {
            blocks[blockIndex].amountOfWeeks = weekIndex;
        }

        if (monthIndex % 2 == 0) {
            ++blockIndex;
        }
    }

    for (int blockIndex = 0; blockIndex < 6; ++blockIndex) {
        std::cout << std::endl << std::endl << blocks[blockIndex].months << std::endl <<
            blocks[blockIndex].weekLine << std::endl;
        for (int line = 0; line < blocks[blockIndex].amountOfWeeks; ++line) {
            std::cout << blocks[blockIndex].days[line] << std::endl;
        }
    }

    return 0;
}
