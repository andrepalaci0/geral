package testesEP2COO.testes;
public class testeStringNumberARGS {
    public static void main(String[] args) {
        String aux = args[0];
        System.out.println(aux);
        String[] splitAux = aux.split("-");
        double n1 = 0;
        double n2 = 0;
        try{
            n1 = Double.parseDouble(splitAux[0]);
            n2 = Double.parseDouble(splitAux[1]);
        }catch(NumberFormatException e){
            System.out.println("Cago no pau ai irmao");
        }
        System.out.println("N1: " + n1);
        System.out.println("N2: " + n2);
    }
}
