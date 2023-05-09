#include <utility>
#include <cstring>


#ifndef LAB3_ABSTRACTCLASS_H
#define LAB3_ABSTRACTCLASS_H

class Object{
public:
    Object(){
        object_count++;
    }
    ~Object(){
        object_count--;
    }

    virtual std::string toString() const = 0;

    static int get_number_of_copies(){
        return Object::object_count;
    }

    static inline int object_count;
};

class Named : public Object{
public:
    explicit Named(std::string data){
        name = std::move(data);
    }
    std::string name;
};

class Task : public Object{
public:
    Task(){
        executed = false;
    };
    virtual void execute() = 0;
    virtual bool hasResult() const = 0;
    bool wasCompleted() const{
        return executed;
    }

protected:
    bool executed;
};

class BinaryTask : public Task{
public:
    BinaryTask() : Task() {}
    bool hasResult() const override{
        return true;
    }
    double getResult() const{
        return result;
    }

protected:
    double first_operand{};
    double second_operand{};
    double result{};
};

class  TaskPlus : public BinaryTask{
public:
    TaskPlus() : BinaryTask() {}
    explicit TaskPlus(double first, double second){
        result = 0;
        first_operand = first;
        second_operand = second;
    }
    void execute() override{
        result = first_operand + second_operand;
        executed = true;
    }
    std::string toString() const override{
        if (wasCompleted()){
            return std::to_string(first_operand) + " + " + std::to_string(second_operand) + " = "
                   + std::to_string(result);
        }
        else return "I have to add " + std::to_string(second_operand) + " and " + std::to_string(first_operand);
    }
};

class  TaskMinus : public BinaryTask{
public:
    TaskMinus() : BinaryTask() {}
    explicit TaskMinus(double first, double second){
        result = 0;
        first_operand = first;
        second_operand = second;
    }
    void execute() override{
        result = first_operand - second_operand;
        executed = true;
    }
    std::string toString() const override{
        if (wasCompleted()){
            return std::to_string(first_operand) + " - " + std::to_string(second_operand) + " = "
                   + std::to_string(result);
        }
        else return "I have to subtract " + std::to_string(second_operand) + " from " + std::to_string(first_operand);
    }
};

class  TaskMultiply : public BinaryTask{
public:
    TaskMultiply() : BinaryTask() {}
    explicit TaskMultiply(double first, double second){
        result = 0;
        first_operand = first;
        second_operand = second;
    }
    void execute() override{
        result = first_operand * second_operand;
        executed = true;
    }
    std::string toString() const override{
        if (wasCompleted()){
            return std::to_string(first_operand) + " * " + std::to_string(second_operand) + " = "
                   + std::to_string(result);
        }
        else return "I have to multiply " + std::to_string(first_operand) + " by " + std::to_string(second_operand);
    }
};

class  TaskDivide : public BinaryTask{
public:
    TaskDivide() : BinaryTask() {}
    explicit TaskDivide(double first, double second){
        result = 0;
        first_operand = first;
        second_operand = second;
    }
    void execute() override{
        result = first_operand / second_operand;
        executed = true;
    }
    std::string toString() const override{
        if (wasCompleted()){
            return std::to_string(first_operand) + " / " + std::to_string(second_operand) + " = "
            + std::to_string(result);
        }
        else{
            return "I have to divide " + std::to_string(first_operand) + " by " + std::to_string(second_operand);
        }
    }
};

class TaskAddAnotherTask : public Task {
public:
    TaskAddAnotherTask(Task* task, Container<Task>* container){
        task_container = container;
        new_task = task;
    }
    void execute() override {
        if (!executed){
            task_container->push_back(new_task);
            executed = true;
        }
        else throw std::runtime_error("Task has already done");
    };
    bool hasResult() const override {
        return false;
    };
    std::string toString() const override{
        if (wasCompleted()){
            return "New task has been added";
        }
        else{
            return "I have to add new task";
        }
    }

private:
    Task* new_task;
    Container<Task>* task_container;
};

class TaskObjCountInContainer : public Task {
public:
    TaskObjCountInContainer(Container<Task>* container){
        result = 0;
        task_container = container;
    }
    void execute() override {
        if (!executed){
            result = task_container->size();
            executed = true;
        }
        else throw std::runtime_error("Task has already done");
    }
    bool hasResult() const override {
        return true;
    };
    std::string toString() const override{
        if (wasCompleted()){
            return "There are " + std::to_string(result) + " Objects in the container";
        }
        else{
            return "I have to count the number of Objects in the container";
        }
    }
private:
    uint32_t result;
    Container<Task>* task_container;
};

class TaskResTaskCountInContainer : public Task {
public:
    TaskResTaskCountInContainer(Container<Task>* container){
        result = 0;
        task_container = container;
    }
    void execute() override {
        if (!executed){
            for (auto x : *task_container){
                result += x->hasResult();
            }
            executed = true;
        }
        else throw std::runtime_error("Task has already done");

    }
    bool hasResult() const override {
        return true;
    };
    std::string toString() const override{
        if (wasCompleted()){
            return "There are " + std::to_string(result) + " Results Task in the container";
        }
        else{
            return "I have to count the number of Results Task in the container";
        }
    }

private:
    int result;
    Container<Task>* task_container;
};

class TaskClearContainer : public Task{
public:
    TaskClearContainer(Container<Task>* container){
        task_container = container;
    }
    void execute() override {
        if (!executed){
            task_container->clear();
            executed = true;
        }
        else throw std::runtime_error("Task has already done");
    }
    bool hasResult() const override {
        return false;
    };
    std::string toString() const override{
        if (wasCompleted()){
            return "Container has been cleaned";
        }
        else{
            return "I have to clean the container";
        }
    }

private:
    Container<Task>* task_container;
};

class TaskObjCount : public Task{
public:
    TaskObjCount(){
        result = 0;
    }
    void execute() override {
        if (!executed){
            result = get_number_of_copies();
            executed = true;
        }
        else throw std::runtime_error("Task has already done");
    }
    bool hasResult() const override {
        return true;
    };
    std::string toString() const override{
        if (wasCompleted()){
            return "There are " + std::to_string(result) + " Objects in program";
        }
        else{
            return "I have to count the number of Objects in the program";
        }
    }

private:
    int result;
};


#endif //LAB3_ABSTRACTCLASS_H
