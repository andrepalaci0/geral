package testesEP2COO.testes;
public class StringManipulation {
    public static void main(String[] args) {

        String teste = "oii";
        teste = addBold(teste);
        System.out.println(teste);
        teste = addSpan(teste);
        System.out.println(teste);
        teste = addColor(teste);
        System.out.println(teste);
    }

    private static boolean hasStyle(String string) {
        String style = "style=\"";
        int index = string.indexOf(style);
        if (index == -1)
            return false;
        else
            return true;
    }

    private static boolean hasSpan(String string) {
        String span = "</span>";
        int index = string.indexOf(span);
        if (index == -1)
            return false;
        else
            return true;
    }

    private static String addSpan(String string){
        String aux;
        if(hasSpan(string)) return string;
        else{
            aux = "</span>";
            String out = string + aux;
            return out;
        }
    }

    private static String addItalic(String string) {
        String aux;
        if (!hasStyle(string)) {
            aux = "<span style=\" font-style:italic; \">";
            return (aux + string);
        } else {
            String style = "style=\"";
            String insert = " font-style:italic;";
            int index = string.indexOf(style);
            String out = string.substring(0, index + style.length()) + insert
                    + string.substring(index + style.length());
            return out;
        }
    }

    private static String addBold(String string) {
        String aux;
        if (!hasStyle(string)) {
            aux = "<span style=\" font-weight:bold; \">";
            return (aux + string);
        } else {
            String style = "style=\"";
            String insert = " font-weight:bold;";
            int index = string.indexOf(style);
            String out = string.substring(0, index + style.length()) + insert
                    + string.substring(index + style.length());
            return out;
        }
    }

    private static String addColor(String string) {
        String color = "#003496";
        String preColor = " color:" + color;
        if (!hasStyle(string)) {
            String aux = "<span style=\""+ preColor + "; \">";
            return (aux + string);
        } else {
            String style = "style=\"";
            String insert = " color:"+ color +";";
            int index = string.indexOf(style);
            String out = string.substring(0, index + style.length()) + insert
                    + string.substring(index + style.length());
            return out;
        }
    }
}
