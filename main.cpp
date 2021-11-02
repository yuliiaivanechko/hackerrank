//
//  main.cpp
//  hackerrank
//
//  Created by Юлія Іванечко on 01.11.2021.
//

#include <iostream>
#include <map>
#include <string>

class parser
{
public:
    void calculate_tags(int lines)
    {
        this->tag_number = lines / 2;
        t = new tag();
        t->tag_alloc(tag_number);
    }
    void parse(std::string line, int line_number)
    {
        if (line_number <= this -> tag_number - 1)
        {
            char sign = 'c';
            int counter = 1;
            std::string tagname = "";
            while(sign != ' ' && sign != '\0')
            {
                tagname += line[counter++];
                sign = line[counter];
            }
            t->set_name(tagname, line_number);
            std::map<std::string, std::string> attrs;
            std::string attribute_name = "", attribute_value = "";
            while (sign == ' ')
            {
                sign = line[counter++];
            }
            counter--;
            while(sign != ' ' && sign != '=' && sign != '\0')
            {
                attribute_name += line[counter++];
                sign = line[counter];
            }
            
            std::size_t found = line.find('"');
            counter = static_cast<int>(found) + 1;
            std::cout<<line[found]<<"\t"<<line[counter]<<std::endl;
            attribute_value += '"';
            while(sign != '"')
            {
                attribute_value += line[counter++];
                sign = line[counter];
            }
            attribute_value += '"';
            attrs.insert({attribute_name,attribute_value});
            
        }
        else
        {}
    }
    
    class tag
    {
        std::string name = "";
        tag* nested_tag = nullptr;
        std::map<char*,char*> attributes;
        int level = 0;
        
    public:
        tag(int level = 0)
        {
            this->level = level;
        }
        void tag_alloc(int depth)
        {
            tag* pointer = this;
            for (int i = 0; i!= depth; ++i)
            {
                pointer->nested_tag = new tag(i);
                pointer = nested_tag;
            }
        }
        void set_name (const std::string& n, int line)
        {
            tag* pointer = this;
            for (int i = 0; i<= line; ++i)
            {
                if (i == line)
                {
                    pointer -> name = n;
                }
                pointer = pointer -> nested_tag;
            }
        }
    };

private:
    tag* t;
    int tag_number = 0;

};

int main(int argc, const char * argv[])
{
    int lines = 0, queries = 0;
    std::string line;
    parser parse_hrml;
    std::cin >> lines >> queries;
    std::cin.ignore(256, '\n');
    parse_hrml.calculate_tags(lines);
    for (int i = 0; i != lines; ++i)
    {
        std::getline(std::cin, line);
        parse_hrml.parse(line, i);    // <tag1 value = "HelloWorld">
    }
    
    return 0;
}
