import java.io.File;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.BufferedWriter;

public class Converter{

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

    static void setUpFile (File outputFile){
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(outputFile.getAbsolutePath()))) {
            bw.write("#separator:|");
            bw.newLine();  // add line break
            bw.write("#notetype:Zusatzinfo_(Automatisieren)");
            bw.newLine();
        } catch (IOException e) {
            System.out.println("Error writing file.");
        }
    }

    static void readFile (File inputFile, File outputFile){
        try (BufferedReader br = new BufferedReader(new FileReader(inputFile.getAbsolutePath()))) {
            String currentLine;
            int line = 0;
            int beginingCard = 1;
            int endingCard =0;

            while ((currentLine = br.readLine()) != null) {
                if(!currentLine.isEmpty() && currentLine.startsWith("###")){
                    endingCard = line;
                    System.out.println(beginingCard + " - " + endingCard);
                    String[] card = extractCard(beginingCard, endingCard, inputFile);
                    writeCard(card, outputFile);
                    beginingCard = endingCard+1;
                }
                line++;
            }
            endingCard = line;
            System.out.println(beginingCard + " - " + endingCard);
            String[] card = extractCard(beginingCard, endingCard, inputFile);
            writeCard(card, outputFile);
            System.out.println("");

        } catch (IOException e) {
            System.out.println("Error reading file.");
        }
    }

    static String[] extractCard(int beginingCard, int endingCard, File inputFile){
        String[] card = new String[5];
        String question = "";
        String anwser = "";
        String info = "";
        String source ="";
        String tags = "";

        if(beginingCard == 1){
            card[0] = question;
            card[1] = anwser;
            card[2] = info;
            card[3] = source;
            card[4] = tags;

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
        card[1] = anwser;
        card[2] = info;
        card[3] = source;
        card[4] = tags;

        card = formatCard(card);

        return card;
    }

    static String[] formatCard(String[] card){
        if (card[0].isEmpty()){
            return card;
        }     

        // Formating the Question correctly
        card[0] = card[0].substring(3);
        card[0] = card[0].trim();
        card[0] = card[0].replaceAll("\\$(.+?)\\$","\\\\($1\\\\)");
        

        // Formating the answer
        String answer  = card[1];

        // Auto placing math-mode
        while(answer.contains("$")){
            answer = answer.replaceFirst("\\$", "\\\\(" );
            answer = answer.replaceFirst("\\$", "\\\\)" );
        }

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

        //bold
        answer = answer.replaceAll("\\*\\*(.+?)\\*\\*","<span style=\"color:limegreen;\">$1</span>");

        //italics
        answer = answer.replaceAll("\\*(.+?)\\*","<span style=\"color:steelblue;\">$1</span>");
        

        // Formating Information
        card[2] = card[2].replaceAll("\\$(.+?)\\$","\\\\($1\\\\)");

        //bold
        card[2] = card[2].replaceAll("\\*\\*(.+?)\\*\\*","<span style=\"color:limegreen;\">$1</span>");

        //italics
        card[2] = card[2].replaceAll("\\*(.+?)\\*","<span style=\"color:steelblue;\">$1</span>");

        // Formating Tags
        card[4] = card[4].replaceFirst("Tags", " ");
        card[4] = card[4].replaceAll("\\W", " ");

        card[1] = answer;

        
        
        
        return card;
    }

    static void writeCard(String[] card, File outputFile){
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(outputFile.getAbsolutePath(), true))) {
            bw.newLine();
            bw.write("\"" + card[0] +"\"" + "|" +"\"" + card[1] +"\"" + "|" +"\"" + card[2] +"\"" + "|" +"\"" + card[3] + "\"" + "|" +"\"" + card[4] + "\"");
        } catch (IOException e) {
            System.out.println("Error writing file.");
        }
    }

    public static void main(String[] args){
        File inputFile = new File(args[0]); // Takes the first Argument and takes it as the input File
        File outputFile = createFile(inputFile); // generating an output File
        setUpFile(outputFile); // adds basic syntax at begining of .txt file
        readFile(inputFile, outputFile);
    }
}