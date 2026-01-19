import java.io.File;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.BufferedWriter;

import Util.FormatCard;

public class Converter{

    static int cardCounter = -1;

    static File createFile (File inputFile){
        try {
            File outputFile = new File("Anki_Files\\"+ inputFile.getName()+ ".txt"); // Create File object
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
            String currentLine;
            int line = 0;
            int beginingCard = 1;
            int endingCard =0;

            while ((currentLine = br.readLine()) != null) {
                if(!currentLine.isEmpty() && currentLine.startsWith("###")){
                    endingCard = line;
                    String[] card = extractCard(beginingCard, endingCard, inputFile);
                    String note = FormatCard.formatNote(card, separator);
                    writeCard(note, outputFile);
                    beginingCard = endingCard+1;
                }
                line++;
            }
            endingCard = line;
            String[] card = extractCard(beginingCard, endingCard, inputFile);
            String note = FormatCard.formatNote(card, separator);
            writeCard(note, outputFile);

        } catch (IOException e) {
            System.out.println("Error reading file.");
        }
    }

    static String[] extractCard(int beginingCard, int endingCard, File inputFile){

        cardCounter +=1;

        String[] card = new String[6];
        String question = "";
        String hint = "";
        String anwser = "";
        String info = "";
        String source ="";
        String tags = "";

        if(beginingCard == 1){
            card[0] = question;
            card[1] = hint;
            card[2] = anwser;
            card[3] = info;
            card[4] = source;
            card[5] = tags;

            return card;
        }

        int line = 1;
        String currentLine = "";

        try (BufferedReader br = new BufferedReader(new FileReader(inputFile.getAbsolutePath()))) {
        

            while(line < beginingCard){
                br.readLine();
                line++;
            }
            
            question = br.readLine();
            
            while(line < endingCard && currentLine.isEmpty()){
                currentLine = br.readLine();
                line++;
            }

        
            if(!currentLine.isEmpty() && currentLine.startsWith("Hinweis:")){
                hint = currentLine;
                currentLine = br.readLine();
            }

            while(line <= endingCard && (!currentLine.startsWith("Informationen:") && !currentLine.startsWith("Quelle:") && !currentLine.startsWith("Tags:"))){
                anwser = anwser + currentLine + "\n";
                currentLine = br.readLine();
                line++;
            }

            while(line <= endingCard && (!currentLine.startsWith("Quelle:") && !currentLine.startsWith("Tags:"))){
                info = info + currentLine;
                currentLine = br.readLine();
                line++;
            }

            
            while(line <= endingCard && !currentLine.startsWith("Tags:")){
                source = source + currentLine;
                currentLine = br.readLine();
                line++;
            }

            while(line <= endingCard){
                tags = tags + currentLine;
                currentLine = br.readLine();
                line++;
            }



        
        } catch (IOException e) {
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