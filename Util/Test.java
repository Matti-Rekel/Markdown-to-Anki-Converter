import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.io.IOException;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Test{
  public static void main (String[] args){
    Path path = Paths.get("/home/Matti/Projekte/Markdown-to-Anki-Converter/Examples/Beispiel.md");
    System.out.println(path.getFileName());
  }
}
