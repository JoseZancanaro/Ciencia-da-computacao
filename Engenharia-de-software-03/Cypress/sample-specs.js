describe("Meu primeiro teste", function() {
    it("Visitar o link em: 'type' ", function() {
        cy.visit("https://example.cypress.io")

        cy.contains("type").click()
    
        cy.url().should("include", "/commands/actions")

        cy.get(".action-email").type("fake@email.com").should("have.value", "fake@email.com")
    })
})