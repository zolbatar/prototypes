package models

import scala.xml._
import play._
import play.libs.Codec;
import com.mongodb.casbah.Imports._
import net.liftweb.json._
import net.liftweb.json.JsonAST
import net.liftweb.json.JsonDSL._

class User(o: DBObject) extends DBInstance("User", o) {
  lazy val oid = o.getAs[ObjectId]("_id")
  lazy val username = o.getAs[String]("username")
  lazy val first_name = o.getAs[String]("first_name")
  lazy val surname = o.getAs[String]("surname")
  lazy val password = o.getAs[String]("password")
  lazy val isAdmin = o.getAs[Boolean]("isAdmin")
  lazy val google_open_id = o.getAs[String]("google_open_id")
  lazy val facebook_id = o.getAs[String]("facebook_id")
  override val ignoreOutput = List("password")
}

object User extends DBBase[User]("Users") {
  def login(username: String, password: String) = findOneBy(MongoDBObject("username" -> username.toLowerCase, "password" -> Codec.hexMD5(password)))

  def login(username: String) = findOneBy(MongoDBObject("username" -> username.toLowerCase))

  def findByUsername(username: String) = findOneBy("username", username.toLowerCase)

  def findByGoogleOpenID(id: String) = findOneBy("google_open_id", id)

  def findByFacebookID(id: String) = findOneBy("facebook_id", id)

  def create(username: String, first_name: String, surname: String, password: String, isAdmin: Boolean, google_open_id: String, facebook_id: String): Boolean = {
    //check whether the user exists
    val user = findByUsername(username)
    user match {
      case Some(_) => false
      case None => {
        val builder = MongoDBObject.newBuilder
        builder += "username" -> username.toLowerCase
        builder += "first_name" -> first_name
        builder += "surname" -> surname
        builder += "password" -> Codec.hexMD5(password)
        if (!isAdmin) {
          builder += "isAdmin" -> checkForFirstUser()
        } else {
          builder += "isAdmin" -> isAdmin
        }
        builder += "google_open_id" -> google_open_id
        builder += "facebook_id" -> facebook_id
        val newObj = builder.result().asDBObject
        coll += newObj
        Logger.info("Created username %s", username.toLowerCase)
        true
      }
    }
  }
  def create(username: String, first_name: String, surname: String, password: String, isAdmin: Boolean): Boolean =
    create(username, first_name, surname, password, isAdmin, "","")

  private var _hasUsers = false

  private def checkForFirstUser() :Boolean = {
    // Called as each user is created, is this our first user, if so, make them a super user
    if (!_hasUsers) {
      if (coll.count == 0) {
        Logger.info("making this user a sys admin")
        _hasUsers = true
        return true
      }
    }
    return false
  }

  def associateWithGoogleOpenID(user: User, id: String) = {
    User.addField(user, "google_open_id", id)
    update(user)
    user
  }

  def disassociateWithGoogleOpenID(user: User) = {
    User.addField(user, "google_open_id", "")
    update(user)
    user
  }

  def associateWithFacebookID(user: User, id: String) = {
    User.addField(user, "facebook_id", id)
    update(user)
    user
  }

  def disassociateWithFacebookID(user: User) = {
    User.addField(user, "facebook_id", "")
    update(user)
    user
  }

  def isAdmin(user: User): Boolean = {
    user.isAdmin match {
      case None => false
      case Some(_) => user.isAdmin.get
    }
  }
}
