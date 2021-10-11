package BRANAS_Nicolas_TP5;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;


/**
 * Une classe qui devait juste servir a afficher les boutons, finalement c'est la classe principale, mais je n'arrive pas à acceder a l'affichage
 * @author nico
 *
 */
public class Layout extends JPanel implements ActionListener{
	
	/**
	 * serial obscure mais necessaire
	 */
	private static final long serialVersionUID = 1L;
	
	/**
	 * equ est un string qui doit etre affiche sur la calculette 
	 */
	private String equ;
	//private Calculatrice c = new Calculatrice();
	
	
	private ArrayList<JButton> liste_boutton;
	
	JButton zero = new JButton("0");
	JButton un= new JButton("1");
	JButton deux= new JButton("2");
	JButton plus= new JButton("+");
	JButton trois= new JButton("3");
	JButton quatre= new JButton("4");
	JButton cinq= new JButton("5");
	JButton moins= new JButton("-");
	JButton six= new JButton("6");
	JButton sept= new JButton("7");
	JButton huit= new JButton("8");
	JButton fois= new JButton("x");
	JButton neuf= new JButton("9");
	JButton point= new JButton(".");
	JButton egal= new JButton("=");
	JButton C= new JButton("C");
	
	
	public Layout(Calculatrice c) {
		
		setLayout(new GridLayout(4,4));
		
		//this.c=c;
		
		liste_boutton = new ArrayList<JButton>();
		equ=new String();
		equ="";
		
		
		this.liste_boutton.add(zero);
		this.liste_boutton.add(un);
		this.liste_boutton.add(deux);
		this.liste_boutton.add(plus);
		this.liste_boutton.add(trois);
		this.liste_boutton.add(quatre);
		this.liste_boutton.add(cinq);
		this.liste_boutton.add(moins);
		this.liste_boutton.add(six);
		this.liste_boutton.add(sept);
		this.liste_boutton.add(huit);
		this.liste_boutton.add(fois);
		this.liste_boutton.add(neuf);
		this.liste_boutton.add(point);
		this.liste_boutton.add(egal);
		this.liste_boutton.add(C);
		
		for (int i = 0; i<liste_boutton.size();i++) {
			this.add(liste_boutton.get(i));
			liste_boutton.get(i).addActionListener(this);
		}
			
		
		//zero.addActionListener(c);
	}


	
	
	/**
	 * fonction qui gere les call backs, tres rudimentaire et qui marche mal
	 */
	@Override
	public void actionPerformed(ActionEvent e) {
		
		String nom = new String();
		nom =e.getActionCommand();
		//System.out.println(nom);
		
		if (e.getSource()==C) {
			equ="";
			//this.c.affichage.setText(equ);
		}
		
		else if (e.getSource()==egal) {
			int a=0;
			int b=0;
			int plus=0;
			int moins=0;
			int fois=0;
			int nbr_flag=0;
			for (int i=0;i<equ.length();i++) {
				if (equ.charAt(i)=='+') {
					if (nbr_flag==1) {
						equ="error";
						break;
					}
					else{
						plus=1;
						nbr_flag++;
					}
				}
				if (equ.charAt(i)=='-') {
					if (nbr_flag==1) {
						equ="error";
						break;
					}
					else{
						moins=1;
						nbr_flag++;
					}
				}
				if (equ.charAt(i)=='x') {
					if (nbr_flag==1) {
						equ="error";
						break;
					}
					else{
						fois=1;
						nbr_flag++;
					}
				}
				else {
					if (nbr_flag==0) a=a*10 +Character.getNumericValue(equ.charAt(i));
					else b=b*10 +Character.getNumericValue(equ.charAt(i));	
				}
				//this.c.affichage.setText(equ);
				
			}
			
			if (plus==1) equ = String.valueOf(a+b);
			else if (moins==1) equ = String.valueOf(a-b);
			else if (fois==1) equ = String.valueOf(a*b);
			System.out.println(equ);
			//this.c.affichage.setText(equ);
			
		}
		
		else {
			//System.out.println(equ);
			equ = equ + nom;
			//System.out.println(nom);
			System.out.println(equ);
			//this.c.affichage.setText(equ);
			
		}
		
	}
	
	/**
	 * main qui permet l'affichage
	 * on cree une JFrame pour avoir une belle fenetre
	 * @param args
	 */
	public static void main (String[] args) {
		
		JFrame ma_fenetre= new JFrame("Calculatrice");
		ma_fenetre.setContentPane(new Calculatrice());
		ma_fenetre.pack();
		ma_fenetre.setVisible(true);
		
	}
	
	

}
