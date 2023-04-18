package entidade;

public class Player implements MobilidadeBasica {
    private String name;

    public void pula() {
        System.out.println(name + " Pulou");
    }

    public void agacha() {
        System.out.println(this.name + " Agachou");
    }
    public void direita(){
        System.out.println(this.name + " Andou p direita");
    }
    public void esquerda(){
        System.out.println(this.name + " Andou p esquerda");
    }

    public void ataca(){
        System.out.println(this.name + " te deu um porradao");
    }

    public Player(String NewName){
        name = NewName;
    }
}