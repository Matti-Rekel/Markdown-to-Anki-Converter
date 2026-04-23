import java.io.File;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.BufferedWriter;
import java.util.ArrayList;
import java.util.regex.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.io.IOException;

import Util.Card;

public class Converter{

  static File createFile (File inputFile){
    try {
       new File("Output").mkdirs(); // Creating an Outputfolder
       File outputFile = new File("Output" +File.separator + inputFile.getName().replaceAll("\\.md", "") + ".txt"); // Create File object
       if (outputFile.createNewFile()) { // Try to create the file
         System.out.println("File created: " + outputFile.getName());
       } else {
         System.out.println("File already exists.");
       }
       return outputFile;
    }
    catch (IOException e) {
       System.out.println("An error occurred when creating the output-File");
       e.printStackTrace(); // Print error details
       return null;
    }
  }

  static void setUpFile (File outputFile, char separator){
    try (BufferedWriter bw = new BufferedWriter(new FileWriter(outputFile.getAbsolutePath()))) {
      // creating the Header for the text-File
      bw.write("#separator:" + separator);
      bw.newLine();
      bw.write("#notetype:Zusatzinfo_(Automatisieren)V_2");
      bw.newLine();
      bw.write("#html:true");
      bw.newLine();
    } catch (IOException e) {
        System.out.println("Error writing basic File header.");
        e.printStackTrace();
    }
  }

  static void convertFile (File inputFile, File outputFile, char separator){
    Path inputFilePath = inputFile.toPath();
    try (BufferedReader br = new BufferedReader(new FileReader(inputFile.getAbsolutePath()))) {
      String currentLine = br.readLine();
      while(currentLine != null){ // While File is not completly read
        ArrayList<String> cardList = new ArrayList<String>();
        boolean nextCard = false;
        // start a new card if line starts with "###"
        if(currentLine != null && currentLine.startsWith("###")){
          nextCard = true;
        }
        while (currentLine != null && (!currentLine.startsWith("###") || nextCard)) {
          nextCard = false;
          cardList.add(currentLine);
          currentLine = br.readLine();
        }

        Card card = Card.formatFields(seperateFields(cardList), inputFilePath, ankiMediaPath); // Formating the Fields after seperating them
        String note = Card.formatCard(card,separator); // Formating the card
        writeCard(note, outputFile); // Writing the Cards into the text-File
      }
    } catch (IOException e) {
      System.out.println("Error reading file.");
      e.printStackTrace();
    }
  }

  // Sperating the ArrayList into seperate Fields
  static Card seperateFields(ArrayList<String> cardList){
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
 
    // counting up on the Card counter
    cardCounter +=1;
 
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

        // Skiping lines starting with ## or #. May add them later as local tags (TODO)
        if (!currentLine.isEmpty() && (currentLine.startsWith("## ") || currentLine.startsWith("# "))){
          continue;
        }

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
      System.out.println("Fehler bei der Karten extraktion");
      e.printStackTrace();
    }

    card.question = question.toString();
    card.hint = hint.toString();
    card.answer = answer.toString();
    card.info = info.toString();
    card.source = source.toString();
    card.tags = tags.toString();
 
    return card;
  }
 
  // Writing note to text-File
  static void writeCard(String note, File outputFile){
    try (BufferedWriter bw = new BufferedWriter(new FileWriter(outputFile.getAbsolutePath(), true))) {
      bw.newLine();
      bw.write(note);
    } catch (IOException e) {
      System.out.println("Error writing note to File.");
      e.printStackTrace();
    }
  }

  static public Path ankiMediaPath; // Variable which saves the Path to the Media directory of your local Anki install were all the pictures are saved
  static int cardCounter = 0; // Counter of how many Cards were created

  public static void main(String[] args){
    char separator = ';'; // Determins how Fields are seperated in the created text-File (for possibilities refer to Anki guid)

    // Try to read or creat a config File in which ankiMediaPath should be stored
    try{
      File config = new File("config.txt");
      if (!config.exists()){
        if (args.length >= 2){
          config.createNewFile();
          BufferedWriter confWriter = new BufferedWriter(new FileWriter(config.getAbsolutePath(), true));
          confWriter.write(args[1]);
          confWriter.close();
        } else{
           System.out.println("Please run the Programm again and give Ankis Media Folder as second Argument");
           return;
        }
      }
      BufferedReader confReader = new BufferedReader(new FileReader(config.getAbsolutePath()));
      ankiMediaPath = Paths.get(confReader.readLine());
    } catch (Exception e) {
      System.out.println("Error reading/writing config File");
      return;
    }

    File inputFile = new File(args[0].replaceAll("\\\\", "\\\\\\\\")); // Takes the first Argument and takes it as the input File (additionally doubeling all inputed \)
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
