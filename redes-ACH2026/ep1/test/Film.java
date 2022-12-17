import java.util.*;

public class Film {
    private String name;
    private int score;
    
    Film(int score, String name) {
        this.name = name;
        this.score = score;
    }

    public String getName () {
        return this.name;
    }

    public int getScore () {
        return this.score;
    }

     public void setScore (int score) {
         this.score = score;
     }
}