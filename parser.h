#include <vector>
#include <string>
#include <sstream>
#include <map>

// Constructor
class parser
{
public:
    std::vector<int> Minutes;
    std::vector<int> Hours;
    std::vector<int> DaysOfMonth;
    std::vector<int> Months;
    std::vector<int> DaysOfWeek;
    std::string Command;

    parser(std::string min, std::string hou, std::string dom, std::string mon, std::string dow, std::string cmd)
    {
        Minutes = parse(min, 0);
        Hours = parse(hou, 1);
        DaysOfMonth = parse(dom, 2);
        Months = parse(mon, 3);
        DaysOfWeek = parse(dow, 4);
        Command = cmd;
    }

    // Print format
    void print()
    {
        printf(
            "minute %s\nhour %s\nday of month %s\nmonth %s\nday of week %s\ncommand %s",
            join(Minutes).c_str(),
            join(Hours).c_str(),
            join(DaysOfMonth).c_str(),
            join(Months).c_str(),
            join(DaysOfWeek).c_str(),
            Command.c_str());
    }

    // Parse method
    std::vector<int> parse(std::string s, int t)
    {
        // Set boundaries for each value
        int beg;
        int end;

        if(t == 0) // Minute
        {
            beg = 0;
            end = 59;
        }
        else if (t == 1) // Hour
        {
            beg = 0;
            end = 23;
        }
        else if (t == 2) // Day of Month
        {
            beg = 1;
            end = 31;
        }
        else if (t == 3) // Month
        {
            beg = 1;
            end = 12;
        }
        else if (t == 4) // Day of Week
        {
            beg = 1;
            end = 7;
        }

        std::vector<int> res; // Vector for result value

        std::map<std::string, std::string> months; // Mapping for month as a word (NOV, JAN etc)

        months["JAN"] = "1";
        months["FEB"] = "2";
        months["MAR"] = "3";
        months["APR"] = "4";
        months["MAY"] = "5";
        months["JUN"] = "6";
        months["JUL"] = "7";
        months["AUG"] = "8";
        months["SEP"] = "9";
        months["OCT"] = "10";
        months["NOV"] = "11";
        months["DEC"] = "12";

        for(std::map<std::string, std::string>::iterator iter = months.begin(); iter != months.end(); ++iter)
        {
            std::string k = iter->first;

            if(s.find(k) != -1)
            {
                s.replace(s.find(k), 3, months[k]);
            }

        } 

        // Star case
        if (s == "*")
        {
            for (int i = beg; i <= end; i++)
            {
                res.push_back(i);
            }
            return res;
        }

        std::vector<std::string> tmp; // Temporary vector
        
        // Coloumn case
        if (s.find(",") != -1)
        {
            std::string sign = ",";
            size_t beg = 0;
            size_t end = 0;
            std::string tok;

            while ((end = s.find(sign, beg)) != -1)
            {
                tok = s.substr(beg, end - beg);
                beg = end + sign.length();
                tmp.push_back(tok);
            }

            tmp.push_back(s.substr(beg));
        }
        else
        {
            tmp.push_back(s);
        }

        // Dash case
        for (int i = 0; i < tmp.size(); i++)
        {
            if (tmp[i].find("-") != -1)
            {
                try
                { 
                    int fir = std::stoi(tmp[i].substr(0, tmp[i].find("-"))); 
                    int sec = std::stoi(tmp[i].substr(tmp[i].find("-") + 1));

                    if (sec < fir)
                    {
                        for (int i = fir; i <= end; i++)
                        {
                        res.push_back(i);
                        }

                        for (int i = beg; i <= sec; i++)
                        {
                        res.push_back(i);
                        }
                    } 
                    else 
                    {
                        for (int i = fir; i <= sec; i++)
                        {
                        res.push_back(i);
                        }
                    }

                    continue;
                }
                catch (const char *error)
                {
                    printf("[Error] %s", error);
                    exit(0);
                }
            }

            // Slash value
            if (tmp[i].find("/") != -1)
            {
                try
                {
                    int fir = (tmp[i].substr(0, tmp[i].find("/")) == "*") ? beg : std::stoi(tmp[i].substr(0, tmp[i].find("/")));
                    int sec = std::stoi(tmp[i].substr(tmp[i].find("/") + 1));

                    if (fir < beg || sec > end)
                    {
                        throw("Incorrect input\n");
                    }

                    for (int i = fir; i <= end; i += sec)
                    {
                        res.push_back(i);
                    }

                    continue;
                }
                catch (const char *error)
                {
                    printf("[Error] %s", error);
                    exit(0);
                }
            }
            res.push_back(std::stoi(tmp[i]));
        }
        return res;
    }

    // Formatting
    std::string join(std::vector<int> &s)
    {
        std::stringstream sstream;
        int i = 0;
        for (auto e : s)
        {
            if (i != 0)
            {
                sstream << " ";
            }
            sstream << e;
            i++;
        }
        return sstream.str();
    }

    // Output formatting for UAT
    std::string output()
    {
        return join(Minutes) + "\n" + join(Hours) + "\n" + join(DaysOfMonth) + "\n" + join(Months) + "\n" + join(DaysOfWeek) + "\n" + Command + "\n";
    }
};