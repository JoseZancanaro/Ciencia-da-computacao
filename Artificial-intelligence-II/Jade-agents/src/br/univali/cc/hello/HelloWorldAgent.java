package br.univali.cc.hello;

import jade.core.Agent;

/*  Program arguments
    -agents
    HelloAgent:br.univali.cc.hello.HelloWorldAgent
*/
public class HelloWorldAgent extends Agent {
    protected void setup() {
        System.out.println("Hello world!");
        System.out.println("My name is: " + this.getLocalName());
    }
}
