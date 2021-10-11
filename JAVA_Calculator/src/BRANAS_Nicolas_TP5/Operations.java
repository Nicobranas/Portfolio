package BRANAS_Nicolas_TP5;

import java.awt.GridLayout;
import javax.swing.JButton;
import javax.swing.*;
import java.awt.*;

public class Operations extends JPanel{
	
	JButton plus= new JButton("+");
	JButton moins= new JButton("-");
	JButton fois= new JButton("x");
	JButton C= new JButton("C");
	
	public Operations() {
		setLayout(new GridLayout(4,1));
		this.add(plus);
		this.add(moins);
		this.add(fois);
		this.add(C);
	}

}
