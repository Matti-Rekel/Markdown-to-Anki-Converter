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
        String answer  = card[1];

        answer = mathMode(answer);

        // orderd and unorderd lists in HTML
        String[] splitAnswer = answer.split("\n");

        for(int i = 0; i < splitAnswer.length; i++){
            int lineListStart = 0;
            int lineListEnd = 0;

            // remove # Lines
            if(!splitAnswer[i].isEmpty() && splitAnswer[i].charAt(0) == '#'){
                splitAnswer[i] = "";
            }


            // Unorderd List
            if(!splitAnswer[i].isEmpty() && splitAnswer[i].charAt(0) == '-'){
                System.out.println("list found");
                lineListStart = i;
                lineListEnd = i -1;
                while(i < splitAnswer.length && !splitAnswer[i].isEmpty() && splitAnswer[i].charAt(0) == '-'){
                    i++;
                    lineListEnd++;
                }

                
                System.out.println(lineListStart + " " + lineListEnd);


                splitAnswer[lineListStart] = splitAnswer[lineListStart].replaceFirst("-", "<ul>  <li>");
                while(lineListStart <= lineListEnd){
                    splitAnswer[lineListStart] = splitAnswer[lineListStart].replaceFirst("-", "<li>");
                    lineListStart++;
                }
                splitAnswer[lineListEnd] = splitAnswer[lineListEnd] + "</ul>";


            }

            
            // Orderd List
            if(i < splitAnswer.length &&!splitAnswer[i].isEmpty() && splitAnswer[i].startsWith("1.")){
                System.out.println("list found");
                lineListStart = i;
                lineListEnd = i -1;
                while(i < splitAnswer.length && !splitAnswer[i].isEmpty() && splitAnswer[i].charAt(1) == '.'){
                    i++;
                    lineListEnd++;
                }

                
                System.out.println(lineListStart + " " + lineListEnd);


                splitAnswer[lineListStart] = splitAnswer[lineListStart].replaceFirst("1.", "<ol>  <li>");
                lineListStart++;
                while(lineListStart <= lineListEnd){
                    splitAnswer[lineListStart] = splitAnswer[lineListStart].replaceFirst(splitAnswer[lineListStart].charAt(0) + ".", "<li>");
                    splitAnswer[lineListStart] = splitAnswer[lineListStart] + "</li>";
                    lineListStart++;
                }
                splitAnswer[lineListEnd] = splitAnswer[lineListEnd] + "</ol>";


            }
        }

        // making the Array a String again
        answer = "";
        for(int i = 0; i < splitAnswer.length; i++){
            answer = answer + splitAnswer[i] + "<br>";
        }


        // Font changes in HTML
        answer = fonts(answer);
        

        // Formating Information
        card[2] = mathMode(card[2]);
        card[2] = fonts(card[2]);

        // Formating Tags
        card[4] = card[4].replaceFirst("Tags", " ");
        card[4] = card[4].replaceAll("\\W", " ");

        card[1] = answer;

        
        
        
        return card;
    }

    private static String mathMode(String field){
        return field = field.replaceAll("\\$(.+?)\\$","\\\\($1\\\\)");
    }

    private static String fonts(String field){
        //bold
        field = field.replaceAll("\\*\\*(.+?)\\*\\*","<span style=\"color:limegreen;\">$1</span>");

        //italics
        field = field.replaceAll("\\*(.+?)\\*","<span style=\"color:steelblue;\">$1</span>");

        return field;
    }
}