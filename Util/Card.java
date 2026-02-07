package Util;

import java.util.*;
import java.util.regex.*;

public class Card{
    public String question = "";
    public String hint = "";
    public String answer = "";
    public String info = "";
    public String source = "";
    public String tags = "";

    public static Card formatCard(Card card){
        if (card.question.isEmpty()){
            return card;
        }     

        // Formating the Question correctly
        card.question = card.question.substring(3);
        card.question = card.question.trim();
        card.question = mathMode(card.question);
        

        // Formating the answer
        card.answer = htmlConform(card.answer);
        card.answer = mathMode(card.answer);
        card.answer = lists(card.answer);
        card.answer = highlight(card.answer);
        card.answer = code(card.answer);
        

        // Formating Information
        if (!card.info.isEmpty())
        card.info = card.info.substring(14);
        card.info = card.info.trim();
        card.info = htmlConform(card.info);
        card.info = mathMode(card.info);
        card.info = lists(card.info);
        card.info = highlight(card.info);
        card.info = code(card.info);

        // Formating Tags
        card.tags = card.tags.replaceFirst("Tags", " ");
        card.tags = card.tags.replaceAll("\\W", " ");
        
        return card;
    }

    public static String formatNote(Card card, char separator){
        String note = "";

        card.question = card.question.replaceAll("\"", "\"\"");
        card.hint  = card.hint.replaceAll("\"", "\"\"");
        card.answer = card.answer.replaceAll("\"", "\"\"");
        card.info = card.info.replaceAll("\"", "\"\"");
        card.source = card.source.replaceAll("\"", "\"\"");
        card.tags = card.tags.replaceAll("\"", "\"\"");

        note = "\"" + card.question + "\"" + separator + "\"" + card.hint + "\""  + separator+ "\"" + card.answer + "\""  + separator +"\"" + card.info + "\"" + separator +"\"" + card.source + "\"" + separator +"\"" + card.tags + "\"";
        return note;
    }

    private static String htmlConform(String field){

        return field = (field.isEmpty() ?  "" :  field.replaceAll("\n", "<br>"));
    }

    private static String mathMode(String field){
        field = field.replaceAll("\\$\\$(.+?)\\$\\$", "\\\\[$1\\\\]");
        return field = field.replaceAll("\\$(.+?)\\$","\\\\($1\\\\)");
    }

    private static String highlight(String field){
        //bold
        field = field.replaceAll("\\*\\*(.+?)\\*\\*","<span class=\"highlight1\">$1</span>");

        //italics
        field = field.replaceAll("\\*(.+?)\\*","<span class=\"highlight2\">$1</span>");

        return field;
    }


    //Lists
    private static final Pattern Orderd_List_Item = Pattern.compile("^(\\s*)([1-9]\\d*)\\.\\s+(.*)$");  // Regex Pattern for orderd Lists
    private static final Pattern Unorderd_List_Item = Pattern.compile("^(\\s*)-\\s+(.*)$");             // Regex Pattern for unorderd Lists
    private static String lists(String field){// orderd and unorderd lists in HTML
        if (field.isEmpty()){
            return "";
        }

        String[] splitField = field.split("<br>");
        StringBuilder html = new StringBuilder();
        int currentIndent_unorderd = 0;
        int currentIndent_orderd = 0;

        for (String line : splitField){
            Matcher matcher_unorderd = Unorderd_List_Item.matcher(line);
            Matcher matcher_orderd = Orderd_List_Item.matcher(line);
            if (matcher_unorderd.find()){
                String leadingSpaces = matcher_unorderd.group(1);
                String content = matcher_unorderd.group(2);

                int indentLevel = (leadingSpaces.length() / 4)+1;

                if (indentLevel > currentIndent_unorderd) {
                    for (int i = currentIndent_unorderd; i < indentLevel; i++){
                        html.append("<ul>");
                    }
                }
                else if (indentLevel < currentIndent_unorderd){
                    for (int i = currentIndent_unorderd; i > indentLevel; i--){
                        html.append("</ul>");
                    }
                }
                currentIndent_unorderd = indentLevel;
                html.append("<li>").append(content).append("</li>");
            }else if(matcher_orderd.find()){
                String leadingSpaces = matcher_orderd.group(1);
                String content = matcher_orderd.group(3);

                int indentLevel = (leadingSpaces.length() / 4) +1;

                if (indentLevel > currentIndent_orderd) {
                    for (int i = currentIndent_orderd; i < indentLevel; i++){
                        html.append("<ol>");
                    }
                }
                else if (indentLevel < currentIndent_orderd){
                    for (int i = currentIndent_orderd; i > indentLevel; i--){
                        html.append("</ol>");
                    }
                }
                currentIndent_orderd = indentLevel;
                html.append("<li>").append(content).append("</li>");

            }else{
                for (int i = currentIndent_orderd; i > 0; i--){
                    html.append("</ol>");
                }
                for (int i = currentIndent_unorderd; i > 0; i--){
                    html.append("</ul>");
                }
        
                html.append(line).append("<br>");
            }
        }
        
        return html.toString();
    }

    private static String code(String field){
        field = field.replace("````java<br>", "<pre class=\"code\">");
        field = field.replace("````", "</pre>");

        return field;
    }

}