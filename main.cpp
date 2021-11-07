//
//  main.cpp
//  hackerrank
//
//  Created by Yuliia Ivanechko on 01.11.2021.
//

//10 10
//<a value = "GoodVal">
//<b value = "BadVal" size = "10">
//</b>
//<c height = "auto">
//<d size = "3">
//<e strength = "2">
//</e>
//</d>
//</c>
//</a>
//a~value
//b~value
//a.b~size
//a.b~value
//a.b.c~height
//a.c~height
//a.d.e~strength
//a.c.d.e~strength
//d~sze
//a.c.d~size

//
//GoodVal
//Not Found!
//10
//BadVal
//Not Found!
//auto
//Not Found!
//2
//Not Found!
//3

#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <vector>

class parser
{
public:
    
    void parse_attributes(std::string& attrs, const std::string t_name)
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
            counter += 2;
            while(sign != '"')
            {
                attr_value += attrs[counter++];
                sign = attrs[counter];
            }
            counter++;
            attributes.insert({attr_name, attr_value});
            attr_name = "";
            attr_value = "";
        }
        auto pred = [=](tag& t){return t.get_name() == t_name;};
        auto it = std::find_if(tags.begin(), tags.end(), pred);
        it->set_attributes(attributes);
        
    }
    
    void parse(std::string line, int line_number)
    {
        if (line[1] != '/')
        {
            char sign = 'c';
            int counter = 1;
            std::string tagname = "";
            while(sign != ' ' && sign != '\0' && sign != '>')
            {
                tagname += line[counter++];
                sign = line[counter];
            }
            tags.push_back(tag(tagname));
            if(sign == '>')
            {
                return;
            }
            std::string rest_of_line = "";
            while(sign != '>')
            {
                rest_of_line += line[counter++];
                sign = line[counter];
            }
            parse_attributes(rest_of_line, tagname);
        }
        else
        {
            std::string tagname = "";
            char sign = 'c';
            std::size_t counter = 2;
            
            while(sign != '>')
            {
                tagname += line[counter++];
                sign = line[counter];
            }
            auto pred = [=](tag& t){return t.get_name() == tagname;};
            auto it = std::find_if(tags.begin(), tags.end(), pred);
            it->opened = false;
        }
    }
    const std::map<std::string, std::string> get_attributes(std::string& tags)
    {
        std::map<std::string, std::string> attrs = this->t->get_attributes();
        return attrs;
    }
    void parse_query(std::string& q)
    {
        char sign = 'l';
        int count = 0;
        std::string name = "";
        while (sign != '~')
        {
            name += q[count++];
            sign = q[count];
        }
        auto atts = this->t->get_attributes();
        std::string key = "";
        count++;
        while (sign != '\0' && sign != '\n')
        {
            key += q[count++];
            sign = q[count];
        }
        if (atts.find(key) == atts.end())
        {
            std::cout<<"Not Found!"<<std::endl;
        }
        else
        {
            std::cout<<atts[key]<<std::endl;
        }
    }
    void display()
    {
        for(const auto& t: tags)
        {
            auto a = t.get_attributes();
            std::cout << t.get_name() << '\t' << t.display_attributes() << '\t' << t.opened << std::endl;
        }
    }
    ~parser()
    {
    }
    
    class tag
    {
        int max_size = 20;
        std::string name = "";
        std::map<std::string, std::string> attributes;

    public:
        
        bool opened = true;
        
        tag(const std::string& n)
        {
            this -> name = n;
        }
        
        const std::string& get_name() const
        {
            return this -> name;
        }
        
        const std::map<std::string, std::string>& get_attributes() const
        {
            return this->attributes;
        }
        std::string display_attributes() const
        {
            std::string atts;
            for(auto& a: attributes)
            {
                atts += a.first + '\t' + a.second + '\t';
            }
            return atts;
        }
        
        void set_attributes(const std::map<std::string, std::string>& attrs)
        {
            this->attributes = attrs;
        }
    };

private:
    tag* t;
    std::vector <tag> tags;

};

int main(int argc, const char * argv[])
{
    int lines = 0, queries = 0;
    std::string line, query;
    parser parse_hrml;
    std::cin >> lines >> queries;
    if (lines > 20)
    {
        lines = 20;
    }
    if (queries > 20)
    {
        queries = 20;
    }
    std::cin.ignore(256, '\n');
    for (int i = 0; i != lines; ++i)
    {
        std::getline(std::cin, line);
        parse_hrml.parse(line, i);
    }
    
    for (int i = 0; i != queries; ++i)
    {
        std::getline(std::cin, query);
        parse_hrml.parse_query(query);
    }
    
    
    return 0;
}
