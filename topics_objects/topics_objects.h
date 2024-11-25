#ifndef TOPICS_OBJECTS_H
#define TOPICS_OBJECTS_H

#include <iostream>
#include <string>

// Base class: Topic
class Topic {
private:
    std::string name;          // Topic name
    std::string description;   // Topic description
    int id;                    // Topic ID

public:
    // Constructor
    Topic(const std::string& nm, int idValue, const std::string& desc) 
        : name(nm), description(desc), id(idValue) {}

    // Destructor
    virtual ~Topic() {
        std::cout << "Destroying Topic: " << name << " (ID: " << id << ")" << std::endl;
    }

    // Getter for name
    std::string getName() const {
        return name;
    }

    // Getter for description
    std::string getDescription() const {
        return description;
    }

    // Setter for name
    void setName(const std::string& nm) {
        name = nm;
    }

    // Setter for description
    void setDescription(const std::string& desc) {
        description = desc;
    }

    // Getter for ID
    int getId() const {
        return id;
    }

    // Setter for ID
    void setId(int idValue) {
        id = idValue;
    }

    // Function to demonstrate code usage
    virtual void codeUsage() const {
        std::cout << "Code Usage for Topic: " << description << std::endl;
    }

    // Function to display an example
    void example() const {
        std::cout << "Example for Topic: " << description << std::endl;
    }

    // Function to practice the topic
    void practice() const {
        std::cout << "Practice for Topic: " << description << std::endl;
    }
};

// Derived class: SubTopic
class SubTopic : public Topic {
private:
    std::string subName;         // SubTopic-specific name
    std::string subDescription;  // SubTopic-specific description
    int subId;                   // SubTopic-specific ID

public:
    // Constructor
    SubTopic(const std::string& baseName, int baseId, const std::string& baseDescription,
             const std::string& subNm, const std::string& subDesc, int subIdValue)
        : Topic(baseName, baseId, baseDescription), subName(subNm), subDescription(subDesc), subId(subIdValue) {}

    // Destructor
    ~SubTopic() override {
        std::cout << "Destroying SubTopic: " << subName << " (Sub ID: " << subId << ")" << std::endl;
    }

    // Getter for subName
    std::string getSubName() const {
        return subName;
    }

    // Setter for subName
    void setSubName(const std::string& nm) {
        subName = nm;
    }

    // Getter for subDescription
    std::string getSubDescription() const {
        return subDescription;
    }

    // Setter for subDescription
    void setSubDescription(const std::string& desc) {
        subDescription = desc;
    }

    // Getter for subId
    int getSubId() const {
        return subId;
    }

    // Setter for subId
    void setSubId(int idValue) {
        subId = idValue;
    }

    // Override codeUsage function
    void codeUsage() const override {
        std::cout << "Code Usage for SubTopic: " << subDescription << std::endl;
    }

    // Additional methods (if needed) can be added here
};

#endif // TOPICS_OBJECTS_H
