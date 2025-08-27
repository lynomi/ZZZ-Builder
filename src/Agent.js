class Agent {
  constructor(rank, name, role, attribute, id, status = true) {
    this.rank = rank;
    this.name = name;
    this.role = role;
    this.attribute = attribute;
    this.id = id;
    this.status = status;
  }

  getRank() {
    return this.rank;
  }

  getStatus() {
    return this.status;
  }

  setStatus(status) {
    this.status = status;
  }

  getID() {
    return this.id;
  }

  getName() {
    return this.name;
  }
}

export default Agent;