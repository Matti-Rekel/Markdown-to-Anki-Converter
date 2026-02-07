import java.io.File;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.BufferedWriter;
import java.util.ArrayList;
import java.util.regex.*;

import Util.Card;

public class Converter{


    static int cardCounter = 0;

    static File createFile (File inputFile){
        try {
            File outputFile = new File("Anki_Files"+ File.separator + inputFile.getName().replaceAll("\\.md", "") + ".txt"); // Create File object
            if (outputFile.createNewFile()) { // Try to create the file
                  System.out.println("File created: " + outputFile.getName());
            } else {
              System.out.println("File already exists.");
            }
            return outputFile;
        }
        catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace(); // Print error details
        }
        return null;
    }

    static void setUpFile (File outputFile, char separator){
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(outputFile.getAbsolutePath()))) {
            bw.write("#separator:" + separator);
            bw.newLine();  // add line break
            bw.write("#notetype:Zusatzinfo_(Automatisieren)V_2");
            bw.newLine();
            bw.write("#html:true");
            bw.newLine();
        } catch (IOException e) {
            System.out.println("Error writing file.");
        }
    }

    static void convertFile (File inputFile, File outputFile, char separator){
        try (BufferedReader br = new BufferedReader(new FileReader(inputFile.getAbsolutePath()))) {
            String currentLine = br.readLine();

            while(currentLine != null){ // While File is not completly read
                ArrayList<String> cardList = new ArrayList<String>();
                boolean nextCard = false;
                if(currentLine != null && currentLine.startsWith("###")){
                    nextCard = true;
                }
                while (currentLine != null && (!currentLine.startsWith("###") || nextCard)) {
                    nextCard = false;
                    cardList.add(currentLine);
                    currentLine = br.readLine();
                }
                Card card = extractCard(cardList, inputFile);
                String note = Card.formatNote(card,separator);
                writeCard(note, outputFile);
            }



        } catch (IOException e) {
            System.out.println("Error reading file.");
        }
    }

    static Card extractCard(ArrayList<String> cardList, File inputFile){
        Card card = new Card();
        StringBuilder question = new StringBuilder();
        StringBuilder hint = new StringBuilder();
        StringBuilder answer = new StringBuilder();
        StringBuilder info = new StringBuilder();
        StringBuilder source = new StringBuilder();
        StringBuilder tags = new StringBuilder();

        if(cardList.isEmpty() || !cardList.get(0).startsWith("###")){
            card.question = "";
            card.hint = "";
            card.answer = "";
            card.info = "";
            card.source = "";
            card.tags = "";

            return card;
        }

        cardCounter +=1;

        int line = 1;

        try {
            
            enum Section {
                NONE,
                QUESTION,
                HINT,
                ANSWER,
                INFO,
                SOURCE,
                TAGS
            }
            Section currentSection = Section.NONE;
            
            for (int i = 0; i < cardList.size(); i++){
                String currentLine = cardList.get(i);

                if(!currentLine.isEmpty() && currentLine.startsWith("###")){
                    currentSection = Section.QUESTION;
                }
                if(!currentLine.isEmpty() && currentLine.startsWith("Hinweis:")){
                    currentSection = Section.HINT;
                }
                if(!currentLine.isEmpty() && currentLine.startsWith("Quelle:")){
                    currentSection = Section.SOURCE;
                }
                if(!currentLine.isEmpty() && currentLine.startsWith("Tags:")){
                    currentSection = Section.TAGS;
                }
                if(!currentLine.isEmpty() && (currentLine.startsWith("Informationen:") || currentLine.startsWith("Beweis:") || currentLine.startsWith("Formel:") )){
                    currentSection = Section.INFO;
                }
                if(currentLine.isEmpty() && currentSection != Section.INFO){
                    currentSection = Section.ANSWER;
                }

                switch (currentSection){
                    case QUESTION -> {question.append(currentLine).append("\n");}
                    case HINT -> {hint.append(currentLine).append("\n");}
                    case SOURCE -> {source.append(currentLine).append("\n");}
                    case TAGS -> {tags.append(currentLine).append("\n");}
                    case INFO -> {info.append(currentLine).append("\n");}
                    case ANSWER -> {answer.append(currentLine).append("\n");}
                }
            }


        } catch (Exception e){
            System.out.println("Error reading file.");
            e.printStackTrace();
        }

        card.question = question.toString();
        card.hint = hint.toString();
        card.answer = answer.toString();
        card.info = info.toString();
        card.source = source.toString();
        card.tags = tags.toString();

        card = Card.formatCard(card);

        return card;
    }

    static void writeCard(String note, File outputFile){
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(outputFile.getAbsolutePath(), true))) {
            bw.newLine();
            bw.write(note);
        } catch (IOException e) {
            System.out.println("Error writing file.");
        }
    }

    public static void main(String[] args){
        char separator = ';'; 
        File inputFile = new File(args[0].replaceAll("\\\\", "\\\\\\\\")); // Takes the first Argument and takes it as the input File
        if (inputFile.exists()){
            File outputFile = createFile(inputFile); // generating an output File
            setUpFile(outputFile, separator); // adds basic syntax at begining of .txt file
            convertFile(inputFile, outputFile, separator);
            System.out.println("Es wurden " + cardCounter + " Karten gefunden");
        }else{
            System.out.println("Die angegebene Datei konnte nicht gefunden werden / existiert nicht. Bitte überprüfe deine Eingabe: " + args[0]);
        }
        
    }
}