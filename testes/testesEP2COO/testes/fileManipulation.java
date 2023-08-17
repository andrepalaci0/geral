package testesEP2COO.testes;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class fileManipulation {
    public static void main(String[] args) {
        String filePath = args[0];
        File csvfile = new File(filePath);

        List<Produto> list = recebeCarregaProdutos(csvfile);

        System.out.println("PRODUTOS:");
        for (Produto p : list) {
            System.out.println(p.getCategoria());
        }

    }

    public static List<Produto> recebeCarregaProdutos(File csvfile) {
        List<Produto> list = new ArrayList<Produto>();
        try (BufferedReader br = new BufferedReader(new FileReader(csvfile))) {

            String linha = br.readLine();
            linha = br.readLine();
            while (linha != null) {

                String[] vetor = linha.split(", ");
                Integer id = Integer.parseInt(vetor[0]);
                String descricao = vetor[1];
                String categoria = vetor[2];
                Integer qntEstoque = Integer.parseInt(vetor[3]);
                Double preco = Double.parseDouble(vetor[4]);

                Produto prod = new ProdutoPadrao(id, descricao, categoria, qntEstoque, preco);
                list.add(prod);

                linha = br.readLine();
            }

        } catch (IOException e) {
            System.out.println("Error: " + e.getMessage());
        }

        return list;
    }
}