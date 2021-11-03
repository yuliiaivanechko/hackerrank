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
    void parse_attributes(std::string& attrs, const int line)
    {
        attrs.erase(std::remove(attrs.begin(),attrs.end(),' '),attrs.end());
        std::map<std::string, std::string> attributes;
        std::string attr_name = "", attr_value = "";
        int counter = 0;
        char sign = attrs[counter];
        while(counter < attrs.length())
        {
            while(sign != '=')
            {
                attr_name += attrs[counter++];
                sign = attrs[counter];
            }
            attr_value += '"';
            counter += 2;
            while(sign != '"')
            {
                attr_value += attrs[counter++];
                sign = attrs[counter];
            }
            counter++;
            attr_value += '"';
            attributes.insert({attr_name, attr_value});
            attr_name = "";
            attr_value = "";
        }
        
        t->set_attributes(attributes, line);
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
            std::string rest_of_line = "";
            while(sign!='>')
            {
                rest_of_line += line[counter++];
                sign = line[counter];
            }
            parse_attributes(rest_of_line, line_number);
        }
        else
        {}
    }
    
    class tag
    {
        std::string name = "";
        tag* nested_tag = nullptr;
        std::map<std::string, std::string> attributes;
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
        void set_name (const std::string& n, const int line)
        {
            tag* pointer = this;
            for (int i = 0; i<= line; ++i)
            {
                if (i == line)
                {
                    pointer -> name = n;
                    return;
                }
                pointer = pointer -> nested_tag;
            }
        }
        
        void set_attributes(const std::map<std::string, std::string>& attrs, const int line)
        {
            tag* pointer = this;
            for(int i = 0; i<= line; ++i)
            {
                if (i == line)
                {
                    pointer -> attributes = attrs;
                    return;
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
        parse_hrml.parse(line, i);
    }
    
    return 0;
}
