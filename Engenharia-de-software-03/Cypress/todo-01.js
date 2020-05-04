describe("First automated test", function() {
    it("Remove all tasks and add new ones", function() {
        cy.visit("https://todolistme.net/")
    
        // Remove all tasks
        cy.get("ul#mytodos").children().each(() => {
            cy.get("ul#mytodos").children().first().each((children) => {
                cy.get(children).find(".delete").click({force: true}).as("task-removed")
            })
        })

        cy.wait(500)

        let tasks = [ "Levar o lixo para fora.", 
                      "Elaborar o desafio do cypress.", 
                      "Continuar a leitura do meu livro." ]

        // Add new tasks
        tasks.forEach(task => {
            cy.get("#additempanel").type(task).type("{enter}").as("task-added")
        }) 
    })
})