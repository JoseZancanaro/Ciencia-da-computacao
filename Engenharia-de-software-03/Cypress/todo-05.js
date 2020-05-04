describe("Fifth automated test", function() {
    it("Copy and remove list, add and edit category", function() {
        cy.visit("https://todolistme.net/")

        // Remove the last list
        cy.get("ul.categorycontainer ").children().last().find(".delete").click({force: true}).as("last-list-removed")

        // Copy the first list and edit the copy name
        let listName = "Minha nova lista";
        cy.get("ul.categorycontainer ").children().first().find(".copylist").click({force: true}).as("first-list-copied")
        cy.get("#updatebox").type(listName).type("{enter}").as("list-edited")

        // Remove the first list
        cy.get("ul.categorycontainer ").children().first().find(".delete").click({force: true}).as("first-list-removed")

        // Add category
        let newCategory = "Minha nova categoria", editCategory = "A melhor categoria"
        cy.get(".adddivider").click()
        cy.get("#updatebox").type(newCategory).type("{enter}").as("category-added")
        
        // Edit category
        cy.get(".categories").last().dblclick()
        cy.get("#updatebox").type(editCategory).type("{enter}").as("category-edited")
    })
})