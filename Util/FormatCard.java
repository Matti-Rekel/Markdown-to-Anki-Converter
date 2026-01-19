package Util;

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
        field = field.replaceAll("\n", "<br>");

        return field;
    }

    private static String mathMode(String field){
        field = field.replaceAll("\\$\\$(.+?)\\$\\$","<div class =\"math\"><anki-mathjax block=\"true\">$1</anki-mathjax></div>");
        return field = field.replaceAll("\\$(.+?)\\$","<span class =\"math\"><anki-mathjax>$1</anki-mathjax></span>");
    }

    private static String highlight(String field){
        //bold
        field = field.replaceAll("\\*\\*(.+?)\\*\\*","<span class=\"highlight1\">$1</span>");

        //italics
        field = field.replaceAll("\\*(.+?)\\*","<span class=\"highlight2\">$1</span>");

        return field;
    }

    private static String lists(String field){
        // orderd and unorderd lists in HTML
        String[] splitField = field.split("<br>");

        for(int i = 0; i < splitField.length; i++){
            int lineListStart = 0;
            int lineListEnd = 0;

            // remove # Lines
            if(!splitField[i].isEmpty() && splitField[i].charAt(0) == '#'){
                splitField[i] = "";
            }


            // Unorderd List
            if(!splitField[i].isEmpty() && splitField[i].charAt(0) == '-'){
                lineListStart = i;
                lineListEnd = i -1;
                while(i < splitField.length && !splitField[i].isEmpty() && splitField[i].charAt(0) == '-'){
                    i++;
                    lineListEnd++;
                }



                splitField[lineListStart] = splitField[lineListStart].replaceFirst("-", "<ul>  <li>");
                while(lineListStart <= lineListEnd){
                    splitField[lineListStart] = splitField[lineListStart].replaceFirst("-", "<li>");
                    lineListStart++;
                }
                splitField[lineListEnd] = splitField[lineListEnd] + "</ul>";


            }

            
            // Orderd List
            if(i < splitField.length &&!splitField[i].isEmpty() && splitField[i].startsWith("1.")){
                lineListStart = i;
                lineListEnd = i -1;
                while(i < splitField.length && !splitField[i].isEmpty() && splitField[i].charAt(1) == '.'){
                    i++;
                    lineListEnd++;
                }

                


                splitField[lineListStart] = splitField[lineListStart].replaceFirst("1.", "<ol>  <li>");
                lineListStart++;
                while(lineListStart <= lineListEnd){
                    splitField[lineListStart] = splitField[lineListStart].replaceFirst(splitField[lineListStart].charAt(0) + ".", "<li>");
                    splitField[lineListStart] = splitField[lineListStart] + "</li>";
                    lineListStart++;
                }
                splitField[lineListEnd] = splitField[lineListEnd] + "</ol>";


            }
        }

        // making the Array a String again
        field = "";
        for(int i = 0; i < splitField.length; i++){
            field = field + splitField[i] + "<br>";
        }
        return field;
    }

    private static String code(String field){
        field = field.replace("````java<br>", "<pre class=\"code\">");
        field = field.replace("````", "</pre>");

        return field;
    }

}