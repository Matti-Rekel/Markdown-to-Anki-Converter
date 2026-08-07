#ifndef PARSER_H
#define PARSER_H
{
    using std::String;


    struct Card {
        String Question;
        String Prerequisites;
        String Hint;
        String Answer;
        String Add_Information;
        String Source;
    };


    auto split_Text(String text) -> Card{
        
    }
}
#endif 
