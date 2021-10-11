package BRANAS_Nicolas_TP5;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

/**
 * classe qui devait etre la principale, mais qui finalement ne sert qu'a la mise en page
 * @author nico
 *
 */
public class Calculatrice extends JPanel /*implements ActionListener*/{

	/**
	 * numero de serie demande par oracle
	 */
	private static final long serialVersionUID = 1L;
	
	private Layout pad = new Layout(this);
	public JTextField affichage=new JTextField(20);
	
	/**
	 * on cree un affiche le champs de texte et les bouttons verticalement grace a la BoxLayout
	 */
	public Calculatrice () {

		setLayout(new BoxLayout(this,BoxLayout.PAGE_AXIS));
		affichage.setEditable(false);
		this.add(affichage);
		this.add(pad);
		
		
	}

	/*@Override
	public void actionPerformed(ActionEvent e) {
		
		System.out.println("action recu");	
		
	}*/
	
	/*public static void main (String[] args) {
		
		JFrame ma_fenetre= new JFrame("Calculatrice");
		ma_fenetre.setContentPane(new Calculatrice());
		ma_fenetre.pack();
		ma_fenetre.setVisible(true);
		
	}*/

	
}
