package Util;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.io.IOException;

import java.util.*;
import java.util.regex.*;

public class Card{
    public String question = "";
    public String hint = "";
    public String answer = "";
    public String info = "";
    public String source = "";
    public String tags = "";

    public static Card formatCard(Card card, Path inputPath){
        if (card.question.isEmpty()){
            return card;
        }     

        // Formating the Question correctly
        card.question = card.question.substring(3);
        card.question = card.question.trim();
        card.question = htmlConform(card.question);
        card.question = mathMode(card.question);
        card.question = lists(card.question);
        card.question = highlight(card.question);
        card.question = code(card.question);
        card.question = card.question.replaceAll("^(?:\\s*<br\\s*/?>\\s*)+|(?:\\s*<br\\s*/?>\\s*)+$", "");


        // Formating Hints
        card.hint = htmlConform(card.hint);
        card.hint = mathMode(card.hint);
        card.hint = lists(card.hint);
        card.hint = highlight(card.hint);
        card.hint = code(card.hint);
        card.hint = card.hint.replaceAll("^(?:\\s*<br\\s*/?>\\s*)+|(?:\\s*<br\\s*/?>\\s*)+$", "");
        

        // Formating the answer
        card.answer = htmlConform(card.answer);
        card.answer = imageHandler(card.answer, inputPath);
        card.answer = mathMode(card.answer);
        card.answer = lists(card.answer);
        card.answer = highlight(card.answer);
        card.answer = code(card.answer);
        card.answer = card.answer.replaceAll("^(?:\\s*<br\\s*/?>\\s*)+|(?:\\s*<br\\s*/?>\\s*)+$", "");


        // Formating Information
        if (!card.info.isEmpty())
        card.info = card.info.replaceFirst("^\\w+:", "");
        card.info = card.info.trim();
        card.info = htmlConform(card.info);
        card.info = mathMode(card.info);
        card.info = lists(card.info);
        card.info = highlight(card.info);
        card.info = code(card.info);
        card.info = card.info.replaceAll("^(?:\\s*<br\\s*/?>\\s*)+|(?:\\s*<br\\s*/?>\\s*)+$", "");

        //Formating Source
        card.source = htmlConform(card.source);
        card.source = mathMode(card.source);
        card.source = lists(card.source);
        card.source = highlight(card.source);
        card.source = code(card.source);
        card.source = card.source.replaceAll("^(?:\\s*<br\\s*/?>\\s*)+|(?:\\s*<br\\s*/?>\\s*)+$", "");

        // Formating Tags
        card.tags = card.tags.replaceFirst("Tags", " ");
        card.tags = card.tags.replaceAll("\\W", " ");
        card.tags = htmlConform(card.tags);
        card.tags = mathMode(card.tags);
        card.tags = lists(card.tags);
        card.tags = highlight(card.tags);
        card.tags = code(card.tags);
        card.tags = card.tags.replaceAll("^(?:\\s*<br\\s*/?>\\s*)+|(?:\\s*<br\\s*/?>\\s*)+$", "");
        
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
    
    //TODO: 
    // - Image Name
    private static String imageHandler (String field, Path fileSource){
      String home = System.getProperty("user.home");
      Path ankiPath = Paths.get(home, ".local", "share", "Anki2", "User 1", "collection.media"); 
      Pattern imagePattern = Pattern.compile("(<img.*?>)");
      Pattern imageSrcPattern = Pattern.compile("src=\\\"(.*?)\\\"");
      Matcher imageMatcher = imagePattern.matcher(field);
      while (imageMatcher.find()){
        Matcher imageSrcMatcher = imageSrcPattern.matcher(imageMatcher.group(1));
        imageSrcMatcher.find();
        Path source = Paths.get(imageSrcMatcher.group(1));
        try {
          if (source.isAbsolute()){
            Files.copy(source, Paths.get(ankiPath + "/" + source.getFileName()), StandardCopyOption.REPLACE_EXISTING);
          } else{
            source = Paths.get(fileSource.getParent() + "/" + source.toString());
            Files.copy(source, Paths.get(ankiPath + "/" + source.getFileName()), StandardCopyOption.REPLACE_EXISTING);
          }
        } catch (IOException e) {
          e.printStackTrace();
        }
      }

      field = field.replaceAll("src=\"[^\"]*?/([^/]+)\"", "src=\"$1\"");
      return field;
  
    }

    private static String mathMode(String field){
        field = field.replaceAll("\\$\\$(.+?)\\$\\$", "<span class =\"math-big\">\\\\[$1\\\\]</span>");
        return field = field.replaceAll("\\$(.+?)\\$","<span class =\"math\">\\\\($1\\\\)</span>");
    }


    private static String highlight(String field){
        //bold and italic
        field = field.replaceAll("\\*\\*\\*(.+?)\\*\\*\\*","<span class=\"definition\">$1</span>");
        
        //bold
        field = field.replaceAll("\\*\\*(.+?)\\*\\*","<span class=\"highlight2\">$1</span>");

        //italics
        field = field.replaceAll("\\*(.+?)\\*","<span class=\"highlight1\">$1</span>");

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
        field = field.replaceAll("````java\\s*<br>(.*)````", "<pre class=\"code\">$1</pre>");
        field = field.replaceAll("````\\s*<br>(.*)````", "<pre class=\"code\">$1</pre>");


        field = field.replaceAll("```java\\s*<br>(.*)```", "<pre class=\"code\">$1</pre>");
        field = field.replaceAll("```\\s*<br>(.*)```", "<pre class=\"code\">$1</pre>");


        return field;
    }

}
