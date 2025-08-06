#ifndef AGENT_H_
#define AGENT_H_
#include <string>
#include <qDebug>

class Agent {
    public:

        Agent() : rank('A'), name(""), specialty(""), attribute(""), ID(0), status(false) {}
    
        Agent(char a_rank, std::string a_name, std::string a_specialty, std::string a_attribute, int a_ID, bool a_status = false)
        : rank(a_rank), name(a_name), specialty(a_specialty), attribute(a_attribute), ID(a_ID), status(a_status) {
            qDebug() << "loaded" << name;
        }
        
        // getters
        bool getStatus() const {return status;}
        char getRank() const {return rank;}
        int getID() const {return ID;}
        std::string getName() const {return name;}
        std::string getAttribute() const {return attribute;}
        std::string getSpecialty() const {return specialty;}

        // setters
        void setStatus(bool s) {status = s;}
        void setRank(char r) {rank = r;}
        void setID(int i) {ID = i;}
        void setName(std::string n) {name = n;}
        void setAttribute(std::string a) {attribute = a;}
        void setSpecialty(std::string s) {specialty = s;}

    private:
        char rank;
        std::string name;   
        std::string specialty;
        std::string attribute;

        // ID used for determining DPS agent priority, supports are all 0
        int ID;

        // represents if agent being used in teams (Y / N / -), default is -
        char status;
};
#endif