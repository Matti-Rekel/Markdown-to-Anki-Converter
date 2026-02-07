import java.io.File;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.BufferedWriter;
import java.util.ArrayList;

import Util.FormatCard;

public class Converter{

    static int cardCounter = 0;

    static File createFile (File inputFile){
        try {
            File outputFile = new File("Anki_Files\\"+ inputFile.getName().replaceAll(".md", "") + ".txt"); // Create File object
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
                while ((currentLine != null && !currentLine.startsWith("###")) || nextCard) {
                    nextCard = false;
                    cardList.add(currentLine);
                    currentLine = br.readLine();
                }
                String[] card = extractCard(cardList, inputFile);
                String note = FormatCard.formatNote(card,separator);
                writeCard(note, outputFile);
            }



        } catch (IOException e) {
            System.out.println("Error reading file.");
        }
    }

    static String[] extractCard(ArrayList<String> cardList, File inputFile){
        String[] card = new String[6];
        String question = "";
        String hint = "";
        String anwser = "";
        String info = "";
        String source ="";
        String tags = "";

        if(cardList.isEmpty() || !cardList.get(0).startsWith("###")){
            card[0] = question;
            card[1] = hint;
            card[2] = anwser;
            card[3] = info;
            card[4] = source;
            card[5] = tags;

            return card;
        }

        cardCounter +=1;

        int line = 1;

        try {
            
            question = cardList.get(0);
            boolean infostart = false;
            
            for (int i = 1; i < cardList.size(); i++){
                String currentLine = cardList.get(i);

                if (!currentLine.isEmpty() && currentLine.startsWith("Hinweis:")){
                    hint = currentLine;
                    continue;
                }else if (!currentLine.isEmpty() && currentLine.startsWith("Quelle:")){
                    source = currentLine;
                    continue;
                }else if (!currentLine.isEmpty() && currentLine.startsWith("Tags:")){
                    tags = currentLine;
                    continue;
                }else if ((!currentLine.isEmpty() && currentLine.startsWith("Informationen:")) || infostart){
                    infostart = true;
                    info = info + currentLine + "\n";
                }else{
                    anwser = anwser + currentLine + "\n";
                }

            }


        } catch (Exception e){
            System.out.println("Error reading file.");
        }

        card[0] = question;
        card[1] = hint;
        card[2] = anwser;
        card[3] = info;
        card[4] = source;
        card[5] = tags;

        card = FormatCard.formatCard(card);

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
        File inputFile = new File(args[0]); // Takes the first Argument and takes it as the input File
        File outputFile = createFile(inputFile); // generating an output File
        setUpFile(outputFile, separator); // adds basic syntax at begining of .txt file
        convertFile(inputFile, outputFile, separator);
        System.out.println("Es wurden " + cardCounter + " Karten gefunden");
    }
}