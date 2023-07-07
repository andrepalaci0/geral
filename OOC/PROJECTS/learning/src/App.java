import java.util.*;
public class App{
    public static void main(String[] args) {
        Scanner sc1 = new Scanner(System.in);
        System.out.println("Insira o tamanho do vetor: ");
        int tamanhoDoVetor = sc1.nextInt();
        int vetor[] = new int[tamanhoDoVetor];
        for (int i = 0; i < tamanhoDoVetor; i++) {
            System.out.println("Insira o número do índice: " + i);
            vetor[i] = sc1.nextInt();
        }
        System.out.println("Numeros do array:");
        for (int i = 0; i < vetor.length; i++) {
            System.out.println(vetor[i]);
        }
        for (int i = 0; i < vetor.length; i++) {
            vetor[i] = vetor[i] * 2;
        }
        System.out.println("Array multiplicado: ");
        for (int i = 0; i < vetor.length; i++) {
            System.out.println(vetor[i]);
        }
        double media = 0;
        for (int i = 0; i < vetor.length; i++) {
            media += vetor[i];
        }
        media = media/vetor.length;
        System.out.println("Media: "+ media);
        sc1.close(); 
    }   
}