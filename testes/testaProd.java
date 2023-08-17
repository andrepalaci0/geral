


public class testaProd{
    
    private String string;
    private Produto prod;
    public testaProd(String string)
    {
        this.string = string;
    }

    public void testando()
    {
        //prod = new ProdutoPadrao(1, "desc", "amor", 15, 36);
        //System.out.println(prod.formataParaImpressao());
        //prod = new ProdutoNegrito(prod);
        //System.out.println(prod.formataParaImpressao());
        //prod = new ProdutoCor(prod, "#003496");
        //System.out.println(prod.formataParaImpressao());
        //prod = new ProdutoItalico(prod);
        //System.out.println(prod.formataParaImpressao());
        System.out.println(hasString(prod));
    }


    public static void main(String[] args) {
        testaProd teste = new testaProd("oiii");
        teste.testando();
    }

    private static boolean hasString(Produto p) {
        String aux = "Teste";
        String maior = "gibas teste no mar";
        int index = maior.indexOf(aux);
        if (index == -1)
            return false;
        return true;
    }
}
