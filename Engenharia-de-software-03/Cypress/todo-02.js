describe("Second automated test", function() {
    it("Remove all tasks, add new ones and edit them", function() {
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

        cy.wait(500);

        let idTasks = 0,
            editTasks = [ "Cozinhar o jantar.", 
                          "Finalizar o trabalho de IA.",
                          "Resolver aquele probleminha no código." ]

        // Edit previously added tasks
        editTasks.forEach(task => {
            cy.get("ul#mytodos").children("#todo_" + idTasks).dblclick()
            cy.get("#updatebox").type(task).type("{enter}").as("task-edited")
            idTasks++
            cy.wait(500)
        })
    })
})