#include "../include/homework.h"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

Homework::Homework(int homeworkId, int courseId, const std::string &homework)
    : homeworkId(homeworkId), courseId(courseId), homework(homework) {}

int Homework::getHomeworkId() const { return homeworkId; }
int Homework::getCourseId() const { return courseId; }
std::string Homework::getHomework() const { return homework; }

void Homework::saveToDatabase()
{
    std::ifstream inputFile("../data/Homeworks.json");
    json homeworks;

    inputFile >> homeworks;
    inputFile.close();

    json newHomework = {
        {"homework_id", homeworkId},
        {"course_id", courseId},
        {"homework", homework}};

    homeworks["homeworks"].push_back(newHomework);

    std::ofstream outputFile("../data/homeworks.json");
    outputFile << homeworks.dump(4);
    outputFile.close();

    std::cout << "homework saved to database!" << std::endl;
}

Homework Homework::loadFromDatabase(int homeworkId)
{
    std::ifstream inputFile("data/homeworks.json");
    json homeworks;
    inputFile >> homeworks;
    inputFile.close();
    int flag = 0;

    for (const auto &homework : homeworks["homeworks"])
    {
        if (homework["homework_id"] == homeworkId)
        {
            flag = 1;
            return Homework(homework["homework_id"], homework["course_id"], homework["homework"]);
        }
    }
    if (flag)
    {
        std::cout << "homework couldnt be found\n";
    }
}