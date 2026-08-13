#ifndef PARSER_H
#define PARSER_H
{
    using std::String;

    struct Card {
        string Question         = "";
        string Prerequisites    = "";
        string Hint             = "";
        string Answer           = "";
        string Add_Information  = "";
        string Source           = "";
    };
    enum class fields{
        Question, Prerequisites, Hint, Answer, Add_Information, Source;
    }


    auto process_file(string file_text) -> void;
    auto split_Text(String text, std::map<string, fields> keywords) -> Card;
    auto parse_md_to_html(string field) -> string;


    split_Text(string text, std::map<string, fields> keywords){
        Card res;

        /* Der Plan:
         * Die Überschrift mit ## ist die Frage. Direkt gefolgt von der Antwort.
         * Die Zusatzfelder werden danach mit ### Makiert.
         * In keywords ist Gespeichert, welche Wörter hinter ### welchem Feld zuzuordnen sind.
         *
         * Potenzielle Fehlerquelle ein Feld wird mehrfach erwähnt.
        /*


    }
}
#endif 
