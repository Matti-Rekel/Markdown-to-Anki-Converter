package Util;

import java.util.*;
import java.util.regex.*;

public abstract class FormatCard{

    public static String[] formatCard(String[] card){
        if (card[0].isEmpty()){
            return card;
        }     

        // Formating the Question correctly
        card[0] = card[0].substring(3);
        card[0] = card[0].trim();
        card[0] = mathMode(card[0]);
        

        // Formating the answer
        card[2] = htmlConform(card[2]);
        card[2] = mathMode(card[2]);
        card[2] = lists(card[2]);
        card[2] = highlight(card[2]);
        card[2] = code(card[2]);
        

        // Formating Information
        card[3] = htmlConform(card[3]);
        card[3] = mathMode(card[3]);
        card[3] = lists(card[3]);
        card[3] = highlight(card[3]);
        card[3] = code(card[3]);

        // Formating Tags
        card[5] = card[5].replaceFirst("Tags", " ");
        card[5] = card[5].replaceAll("\\W", " ");
        
        return card;
    }

    public static String formatNote(String[] card, char separator){
        String note = "";

        card[0] = card[0].replaceAll("\"", "\"\"");
        card[1] = card[1].replaceAll("\"", "\"\"");
        card[2] = card[2].replaceAll("\"", "\"\"");
        card[3] = card[3].replaceAll("\"", "\"\"");
        card[4] = card[4].replaceAll("\"", "\"\"");
        card[5] = card[5].replaceAll("\"", "\"\"");

        note = "\"" + card[0] + "\"" + separator + "\"" + card[1] + "\""  + separator+ "\"" + card[2] + "\""  + separator +"\"" + card[3] + "\"" + separator +"\"" + card[4] + "\"" + separator +"\"" + card[5] + "\"";
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
    private static final Pattern Orderd_List_Item = Pattern.compile("^(\\s*)([1-9]\\d*)\\.\\s+(.*)$");
    private static final Pattern Unorderd_List_Item = Pattern.compile("^(\\s*)-\\s+(.*)$");
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